#!/usr/bin/env bash
# Ejecuta los casos de test de la etapa 1 del compilador c-tds
# (analisis lexico y sintactico).
#
# Convencion de nombres dentro de tests/casos:
#   ok_*.ctds     compila (parse) en exit 0; genera <base>.sint
#                 que debe ser identico a expected/<base>.sint.
#   scan_*.ctds   se compila con -target scan (exit 0); genera
#                 <base>.lex identico a expected/<base>.lex.
#   bad_*.ctds    debe fallar (exit != 0), sin archivo de salida;
#                 stderr debe contener expected/<base>.err.
#
# Uso: ./tests/run_tests.sh        (tambien: make test)

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN="${BIN:-$SCRIPT_DIR/../c-tds}"
[ -x "$BIN" ] || BIN="$BIN.exe"
if [ ! -x "$BIN" ]; then
  echo "error: no se encuentra el ejecutable '$BIN' (compile antes con 'make')" >&2
  exit 1
fi

CASOS="$SCRIPT_DIR/casos"
EXP="$SCRIPT_DIR/expected"
OUT="$SCRIPT_DIR/_out"

rm -rf "$OUT"
mkdir -p "$OUT"

passed=0
failed=0

report_fail() { echo "FALLO: $1"; failed=$((failed + 1)); }
report_ok()   { passed=$((passed + 1)); }

# --- casos validos: parse en exit 0, .sint identico, stdout vacio ---
for fuente in "$CASOS"/ok_*.ctds; do
  [ -e "$fuente" ] || continue
  base="$(basename "$fuente" .ctds)"
  cp "$fuente" "$OUT/$base.ctds"
  ( cd "$OUT" && "$BIN" "$base.ctds" ) >"$OUT/$base.stdout" 2>"$OUT/$base.stderr"
  rc=$?
  if [ "$rc" -ne 0 ]; then
    report_fail "$base: exit = $rc (se esperaba 0)"
    sed 's/^/    [stderr] /' "$OUT/$base.stderr" | head -5
    continue
  fi
  if [ -s "$OUT/$base.stdout" ]; then
    report_fail "$base: stdout no vacio en compilacion exitosa"
    continue
  fi
  if ! diff -q --strip-trailing-cr "$OUT/$base.sint" "$EXP/$base.sint" >/dev/null 2>&1; then
    report_fail "$base: .sint difiere de expected/$base.sint"
    diff --strip-trailing-cr "$OUT/$base.sint" "$EXP/$base.sint" | sed 's/^/    /' | head -20
    continue
  fi
  report_ok
done

# --- casos solo scan: -target scan, .lex identico ---
for fuente in "$CASOS"/scan_*.ctds; do
  [ -e "$fuente" ] || continue
  base="$(basename "$fuente" .ctds)"
  cp "$fuente" "$OUT/$base.ctds"
  ( cd "$OUT" && "$BIN" -target scan "$base.ctds" ) >"$OUT/$base.stdout" 2>"$OUT/$base.stderr"
  rc=$?
  if [ "$rc" -ne 0 ]; then
    report_fail "$base: exit = $rc en -target scan"
    sed 's/^/    [stderr] /' "$OUT/$base.stderr" | head -5
    continue
  fi
  if ! diff -q --strip-trailing-cr "$OUT/$base.lex" "$EXP/$base.lex" >/dev/null 2>&1; then
    report_fail "$base: .lex difiere de expected/$base.lex"
    diff --strip-trailing-cr "$OUT/$base.lex" "$EXP/$base.lex" | sed 's/^/    /' | head -20
    continue
  fi
  report_ok
done

# --- casos invalidos: fallar, sin archivo de salida, stderr con patron ---
for fuente in "$CASOS"/bad_*.ctds; do
  [ -e "$fuente" ] || continue
  base="$(basename "$fuente" .ctds)"
  cp "$fuente" "$OUT/$base.ctds"
  ( cd "$OUT" && "$BIN" "$base.ctds" ) >"$OUT/$base.stdout" 2>"$OUT/$base.stderr"
  rc=$?
  if [ "$rc" -eq 0 ]; then
    report_fail "$base: exit = 0 (se esperaba un error)"
    continue
  fi
  if [ -e "$OUT/$base.sint" ]; then
    report_fail "$base: se genero archivo de salida en un caso de error"
    continue
  fi
  patron="$(cat "$EXP/$base.err" 2>/dev/null)"
  if [ -z "$patron" ]; then
    report_fail "$base: falta expected/$base.err"
    continue
  fi
  if ! grep -F "$patron" "$OUT/$base.stderr" >/dev/null 2>&1; then
    report_fail "$base: stderr no contiene '$patron'"
    sed 's/^/    [stderr] /' "$OUT/$base.stderr" | head -10
    continue
  fi
  report_ok
done

echo
echo "Resultado: $passed aprobados, $failed fallidos"
[ "$failed" -eq 0 ]