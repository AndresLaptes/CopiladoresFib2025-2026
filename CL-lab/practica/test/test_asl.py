import sys
import os
import subprocess
import difflib

def print_diff(salida_esperada, salida_tuya, file_esperado):
    """Genera y muestra el diff visual"""
    print("-" * 40)
    diff = difflib.unified_diff(
        salida_esperada.splitlines(keepends=True),
        salida_tuya.splitlines(keepends=True),
        fromfile=f'Esperado ({file_esperado})',
        tofile='Tu salida',
        n=2
    )
    sys.stdout.writelines(diff)
    print("-" * 40 + "\n")

def run_chkt_test(num_str):
    """Test para Type Checking (Semántica)"""
    asl_file = f"../examples/jp_chkt_{num_str}.asl"
    err_file = f"../examples/jp_chkt_{num_str}.err"

    if not os.path.exists(asl_file) or not os.path.exists(err_file):
        print(f"⚠️  Test CHKT {num_str}: Archivos no encontrados ({asl_file} o {err_file}).")
        return

    try:
        # Ejecuta tu compilador
        result = subprocess.run(["./asl", asl_file], capture_output=True, text=True)
        salida_asl = result.stdout + result.stderr 
    except FileNotFoundError:
        print("❌ Error: No se encuentra './asl'.")
        return

    with open(err_file, 'r') as f:
        salida_esperada = f.read()

    if salida_asl == salida_esperada:
        print(f"✅ Test CHKT {num_str}: PASSED")
    else:
        print(f"❌ Test CHKT {num_str}: FAILED")
        print_diff(salida_esperada, salida_asl, err_file)

def run_genc_test(num_str):
    """Test para Generación de Código (LLVM) basándose en checkLLVM.sh"""
    asl_file = f"../examples/jp_genc_{num_str}.asl"
    out_file = f"../examples/jp_genc_{num_str}.out"
    in_file  = f"../examples/jp_genc_{num_str}.in"

    if not os.path.exists(asl_file) or not os.path.exists(out_file):
        print(f"⚠️  Test GENC {num_str}: Archivos no encontrados ({asl_file} o {out_file}).")
        return

    # 1. Ejecutar ./asl para generar el .ll
    try:
        res_asl = subprocess.run(["./asl", asl_file], capture_output=True, text=True)
        if res_asl.returncode != 0:
            print(f"❌ Test GENC {num_str}: FAILED (Error compilando ASL)")
            print(res_asl.stderr)
            return
    except FileNotFoundError:
        print("❌ Error: No se encuentra './asl'.")
        return

    # El script checkLLVM.sh asume que el .ll se genera en la carpeta actual
    ll_file = os.path.basename(asl_file).replace(".asl", ".ll")
    if not os.path.exists(ll_file):
        print(f"❌ Test GENC {num_str}: FAILED (No se generó el archivo {ll_file})")
        return

    # 2. Compilar LLVM IR con clang
    res_clang = subprocess.run(["clang", "-Wno-override-module", ll_file], capture_output=True, text=True)
    if res_clang.returncode != 0:
        print(f"❌ Test GENC {num_str}: FAILED (Error de Clang al generar ejecutable)")
        print(res_clang.stderr)
        return

    # 3. Leer archivo .in si existe para pasarlo por stdin
    stdin_content = None
    if os.path.exists(in_file):
        with open(in_file, 'r') as f:
            stdin_content = f.read()

    # 4. Ejecutar a.out pasándole el contenido del .in
    res_exec = subprocess.run(["./a.out"], input=stdin_content, capture_output=True, text=True)
    salida_generada = res_exec.stdout

    # 5. Comparar con el .out
    with open(out_file, 'r') as f:
        salida_esperada = f.read()

    if salida_generada == salida_esperada:
        print(f"✅ Test GENC {num_str}: PASSED")
    else:
        print(f"❌ Test GENC {num_str}: FAILED")
        print_diff(salida_esperada, salida_generada, out_file)

    # 6. Limpiar archivos temporales
    if os.path.exists(ll_file): os.remove(ll_file)
    if os.path.exists("a.out"): os.remove("a.out")


def main():
    if len(sys.argv) != 3:
        print("Uso correcto:")
        print("  python3 test_asl.py <modo> <numero/rango>")
        print("\nModos:")
        print("  chkt  -> Semántica (jp_chkt_XX)")
        print("  genc  -> Generación LLVM (jp_genc_XX)")
        print("\nEjemplos:")
        print("  python3 test_asl.py chkt 1")
        print("  python3 test_asl.py genc 1-5")
        sys.exit(1)

    mode = sys.argv[1].lower()
    arg_num = sys.argv[2]

    if mode not in ["chkt", "genc"]:
        print("❌ Error: El modo debe ser 'chkt' o 'genc'.")
        sys.exit(1)

    if "-" in arg_num:
        try:
            start, end = map(int, arg_num.split("-"))
            for i in range(start, end + 1):
                num_str = f"{i:02d}"
                if mode == "chkt":
                    run_chkt_test(num_str)
                else:
                    run_genc_test(num_str)
        except ValueError:
            print("❌ Formato de rango inválido. Usa inicio-fin (ej: 1-5)")
    else:
        try:
            num_str = f"{int(arg_num):02d}"
            if mode == "chkt":
                run_chkt_test(num_str)
            else:
                run_genc_test(num_str)
        except ValueError:
            print("❌ Por favor, introduce un número o rango válido.")

if __name__ == "__main__":
    main()