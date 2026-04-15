import sys
import os
import subprocess
import difflib

def run_test(folder_name, test_pattern):
    # Construimos la ruta a la carpeta (asumiendo que están al mismo nivel que 'practica')
    folder_path = os.path.abspath(os.path.join("..", folder_name))
    
    # Si el patrón es un número, lo formateamos a dos dígitos
    if test_pattern.isdigit():
        test_pattern = f"jp_chkt_{int(test_pattern):02d}"
    
    asl_file = os.path.join(folder_path, f"{test_pattern}.asl")
    err_file = os.path.join(folder_path, f"{test_pattern}.err")

    if not os.path.exists(asl_file):
        print(f"⚠️  No encontrado: {asl_file}")
        return

    # Ejecutar el compilador
    try:
        # Usamos stderr=subprocess.STDOUT para capturar errores del compilador
        result = subprocess.run(["./asl", asl_file], capture_output=True, text=True)
        salida_asl = result.stdout + result.stderr 
    except FileNotFoundError:
        print("❌ Error: Ejecutable './asl' no encontrado.")
        return

    # Comparación si existe archivo .err
    if os.path.exists(err_file):
        with open(err_file, 'r') as f:
            salida_esperada = f.read()

        if salida_asl.strip() == salida_esperada.strip():
            print(f"✅ {test_pattern}: PASSED")
        else:
            print(f"❌ {test_pattern}: FAILED (Diff abajo)")
            diff = difflib.unified_diff(
                salida_esperada.splitlines(keepends=True),
                salida_asl.splitlines(keepends=True),
                fromfile='Esperado', tofile='Tu salida', n=1
            )
            sys.stdout.writelines(diff)
    else:
        print(f"ℹ️  {test_pattern}: Ejecutado (no hay archivo .err para comparar)")
        print(f"Salida actual:\n{salida_asl}")

def main():
    if len(sys.argv) < 3:
        print("Uso:")
        print("  python3 test.py <carpeta> <test>         (Ej: python3 test.py jps 02)")
        print("  python3 test.py <carpeta> <inicio-fin>   (Ej: python3 test.py jps 1-10)")
        print("  python3 test.py <carpeta> <nombre>       (Ej: python3 test.py examples helloworld)")
        sys.exit(1)

    folder = sys.argv[1]
    arg_test = sys.argv[2]

    if "-" in arg_test:
        try:
            start, end = map(int, arg_test.split("-"))
            for i in range(start, end + 1):
                run_test(folder, str(i))
        except ValueError:
            print("Rango inválido.")
    else:
        run_test(folder, arg_test)

if __name__ == "__main__":
    main()