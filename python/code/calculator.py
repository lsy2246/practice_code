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

    return formula


def compute(formula):
    if len(formula) == 1:
        return formula[0]
    else:
        for index, item in enumerate(formula):
            if item in ['+', '-', '*', '/', '%']:
                match item:
                    case '+':
                        formula[index - 2] = float(formula[index - 2]) + float(formula[index - 1])
                    case '-':
                        formula[index - 2] = float(formula[index - 2]) - float(formula[index - 1])
                    case '*':
                        formula[index - 2] = float(formula[index - 2]) * float(formula[index - 1])
                    case '/':
                        formula[index - 2] = float(formula[index - 2]) / float(formula[index - 1])
                    case '%':
                        formula[index - 2] = float(formula[index - 2]) % float(formula[index - 1])
                formula.pop(index - 1)
                formula.pop(index - 1)
                formula = compute(formula)
                return formula


Equation = "3%2"
formula = format_data(Equation)
result = compute(formula)
print(result)