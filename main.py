

def read_rom():

    with open('microprog.rom', 'rb') as rom:
        # data = rom.read(8)
        # print(data)
        # print('{:0>8b}'.format(int.from_bytes(data, byteorder='big')))
        cmds = rom.read()

        for i in range(0, len(cmds), 8):
            print('ADDR = 0x%03X' % i)
            hex_str = ''
            fmt_str = ''

            for j in range(5):
                hex_str += '  0x{:02X}'.format(cmds[i + 4 - j]) + 3 * ' '
                fmt_str += '{:0>8b} '.format(cmds[i + 4 - j])

            print(hex_str)
            print(fmt_str)
            print('')

def main():
    read_rom()


if __name__ == '__main__':
    read_rom()