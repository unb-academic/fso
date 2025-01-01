from time import time
from subprocess import run, CalledProcessError


def execute(command: str, argument: str) -> float:
    start = time()

    try:
        result = run([command, argument], capture_output=True, check=True)
        delta = time() - start

        if result.stdout:
            print(result.stdout.decode("utf-8"), end="")

        print(f"> Demorou {delta:.1f} segundos, retornou {result.returncode}")
    except OSError as e:
        delta = time() - start

        print(f"> Erro: {e.strerror}")
        print(f"> Demorou {delta:.1f} segundos, retornou {e.errno}")
    except CalledProcessError as e:
        delta = time() - start

        print(f"> Demorou {delta:.1f} segundos, retornou {e.returncode}")

    return delta


def main() -> None:
    total = 0.0

    while True:
        try:
            total += execute(*input().split())
        except EOFError:
            break

    print(f">> O tempo total foi de {total:.1f} segundos")



if __name__ == "__main__":
    main()
