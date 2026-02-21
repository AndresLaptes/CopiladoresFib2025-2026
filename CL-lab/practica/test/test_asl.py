import sys
import os
import subprocess
import difflib

def run_test(test_num):
    # Formateamos el número a 2 dígitos (ej: 1 -> "01", 12 -> "12")
    num_str = f"{test_num:02d}"
    
    # Construimos las rutas relativas a tus archivos
    asl_file = f"../examples/jp_chkt_{num_str}.asl"
    err_file = f"../examples/jp_chkt_{num_str}.err"

    # Verificamos que los archivos del test existan
    if not os.path.exists(asl_file):
        print(f"⚠️  Test {num_str}: Archivo {asl_file} no encontrado.")
        return
    if not os.path.exists(err_file):
        print(f"⚠️  Test {num_str}: Archivo esperado {err_file} no encontrado.")
        return

    # Ejecutamos tu compilador ./asl
    try:
        # capture_output=True guarda lo que imprime tu programa
        # text=True lo devuelve como string en lugar de bytes
        result = subprocess.run(["./asl", asl_file], capture_output=True, text=True)
        
        # Juntamos la salida estándar (cout) y la de error (cerr) por si acaso
        salida_asl = result.stdout + result.stderr 
    except FileNotFoundError:
        print("❌ Error: No se encuentra './asl'. ¿Has compilado con 'make asl'?")
        return

    # Leemos la salida que el profesor espera
    with open(err_file, 'r') as f:
        salida_esperada = f.read()

    # Comparamos las salidas
    if salida_asl == salida_esperada:
        print(f"✅ Test {num_str}: PASSED")
    else:
        print(f"❌ Test {num_str}: FAILED")
        print("-" * 40)
        
        # Generamos un diff visual y bonito (estilo GitHub)
        diff = difflib.unified_diff(
            salida_esperada.splitlines(keepends=True),
            salida_asl.splitlines(keepends=True),
            fromfile=f'Esperado ({err_file})',
            tofile='Tu salida (./asl)',
            n=2 # Número de líneas de contexto a mostrar
        )
        # Imprimimos el diff
        sys.stdout.writelines(diff)
        print("-" * 40 + "\n")

def main():
    # Comprobamos que el usuario ha pasado argumentos
    if len(sys.argv) != 2:
        print("Uso correcto:")
        print("  python3 test.py <numero>      (Ej: python3 test.py 1)")
        print("  python3 test.py <inicio-fin>  (Ej: python3 test.py 1-5)")
        sys.exit(1)

    arg = sys.argv[1]
    
    # Si detecta un guion, tratamos el input como un rango
    if "-" in arg:
        try:
            start, end = map(int, arg.split("-"))
            for i in range(start, end + 1):
                run_test(i)
        except ValueError:
            print("Formato de rango inválido. Usa inicio-fin (ej: 1-5)")
    else:
        # Si no, es un solo número
        try:
            run_test(int(arg))
        except ValueError:
            print("Por favor, introduce un número o rango válido.")

if __name__ == "__main__":
    main()