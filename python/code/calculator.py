def format_data(data):
    new_data_list = ['']
    for i in data:
        if new_data_list[-1].isdigit() and i.isdigit():
            new_data_list[-1] += i
        else:
            new_data_list.append(i)
    new_data_list.pop(0)
    _static_tmp = []
    formula = []

    for single_item in new_data_list:
        if single_item.isdigit():
            formula.append(single_item)
        elif single_item == '(':
            _static_tmp.append(single_item)
        elif single_item == ')':
            while True:
                tmp_symbol = _static_tmp.pop(-1)
                if tmp_symbol != '(':
                    formula.append(tmp_symbol)
                else:
                    break
        elif single_item in ['*', '/', '%']:
            if not _static_tmp:
                _static_tmp.append(single_item)
            else:
                tmp_symbol = _static_tmp.pop(-1)
                if tmp_symbol == '(':
                    _static_tmp.append(tmp_symbol)
                    _static_tmp.append(single_item)
                elif tmp_symbol in ['*', '/', '%']:
                    formula.append(tmp_symbol)
                    _static_tmp.append(single_item)
                elif tmp_symbol in ['+', '-']:
                    _static_tmp.append(tmp_symbol)
                    _static_tmp.append(single_item)
        elif single_item in ['+', '-']:
            if not _static_tmp:
                _static_tmp.append(single_item)
            else:
                tmp_symbol = _static_tmp.pop(-1)
                if tmp_symbol in ['+', '-', '*', '/', '%']:
                    formula.append(tmp_symbol)
                    _static_tmp.append(single_item)
                elif tmp_symbol == '(':
                    _static_tmp.append(tmp_symbol)
                    _static_tmp.append(single_item)
        elif single_item == '=':
            break
    while _static_tmp:
        formula.append(_static_tmp.pop(-1))

    numbers_stack = []
    while formula:
        single_item = formula.pop(0)
        if single_item.isdigit():
            numbers_stack.append(single_item)
        else:
            number2 = float(numbers_stack.pop(-1))
            number1 = float(numbers_stack.pop(-1))
            match single_item:
                case '+':
                    numbers_stack.append(number1 + number2)
                case '-':
                    numbers_stack.append(number1 - number2)
                case '*':
                    numbers_stack.append(number1 * number2)
                case '/':
                    numbers_stack.append(number1 / number2)
                case '%':
                    numbers_stack.append(number1 % number2)
    return numbers_stack[0]

Equation = "1+2/2+(3*3+2)"
print(format_data(Equation))