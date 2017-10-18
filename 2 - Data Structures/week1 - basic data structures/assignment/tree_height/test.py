#! /usr/bin/env python3

import os


def main():
    for fname in os.listdir("tests"):
        if fname.endswith(".a"):
            continue
        print(fname, end="\t", flush=True)
        os.system(f"./tree_height.out < tests/{fname}")


if __name__ == "__main__":
    main()
