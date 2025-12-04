import sympy as sp
import re

#函数：求解方程组
#返回值：字典，如{'R2',1000,'R1',2000}
def solve_equations(equations_str, variables):
    """解析并求解方程"""
    # 提取所有变量名
    all_symbols = set()
    for eq_str in equations_str:
        # 使用正则表达式提取变量名 (简单方法，适用于简单变量名)
        # 匹配由字母、数字和下划线组成的变量名，但不能以数字开头
        symbols_in_eq = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', eq_str)
        all_symbols.update(symbols_in_eq)
    
    # 移除可能的函数名和常量
    excluded = {'sin', 'cos', 'tan', 'log', 'ln', 'exp', 'sqrt', 'pi', 'e'}
    all_symbols = all_symbols - excluded
    
    # 创建符号
    symbols_dict = {}
    for symbol in all_symbols:
        symbols_dict[symbol] = sp.symbols(symbol)
    
    # 解析方程
    equations = []
    for eq_str in equations_str:
        try:
            # 分离等号两边
            if '=' in eq_str:
                lhs_str, rhs_str = eq_str.split('=', 1)
                lhs = sp.sympify(lhs_str.strip(), locals=symbols_dict)
                rhs = sp.sympify(rhs_str.strip(), locals=symbols_dict)
                equations.append(sp.Eq(lhs, rhs))
            else:
                # 如果没有等号，假设是表达式=0
                expr = sp.sympify(eq_str.strip(), locals=symbols_dict)
                equations.append(sp.Eq(expr, 0))
        except Exception as e:
            print(f"方程解析错误 '{eq_str}': {e}")
            return None
    
    # 准备已知值和未知变量
    known_values = {}
    unknown_vars = []
    
    for var_name, value in variables.items():
        if var_name not in symbols_dict:
            print(f"警告: 变量 '{var_name}' 在方程中未使用")
            continue
            
        if value is None:
            unknown_vars.append(symbols_dict[var_name])
        else:
            known_values[symbols_dict[var_name]] = value
    
    # 检查方程和未知变量数量
    if len(unknown_vars) == 0:
        print("所有变量都已定义，无需计算")
        return None
    
    if len(unknown_vars) > len(equations):
        print(f"错误: 未知变量数量({len(unknown_vars)})多于方程数量({len(equations)})")
        return None
    
    # 求解方程
    try:
        # 代入已知值
        equations_with_values = [eq.subs(known_values) for eq in equations]
        
        # 求解
        if len(unknown_vars) == 1 and len(equations) == 1:
            # 单变量单方程
            solution = sp.solve(equations_with_values[0], unknown_vars[0])
        else:
            # 多变量或多方程
            solution = sp.solve(equations_with_values, unknown_vars)
        
        if not solution:
            print("无解")
            return None
        
        # 处理解的形式
        if isinstance(solution, list):
            # 可能有多个解
            if len(solution) == 1:
                solution = solution[0]
            else:
                print(f"找到 {len(solution)} 个解:")
                for i, sol in enumerate(solution):
                    print(f"  解 {i+1}: {sol}")
                # 取第一个解
                solution = solution[0]
        
        # 返回结果
        if len(unknown_vars) == 1:
            result = {str(unknown_vars[0]): float(solution)}
        else:
            result = {}
            for var, val in solution.items():
                result[str(var)] = float(val)
        # 更新原始变量（可选）
        for var_name, value in result.items():
            if var_name in globals():
                globals()[var_name] = value     
        return result
            
    except Exception as e:
        print(f"求解错误: {e}")
        return None




print("####################################")
print("#光耦电阻计算 R20")
print("####################################")
Vin_AC = 230
R20_Ploss = 1 * 0.33
R20 = Vin_AC**2 / R20_Ploss
print("R20 = ",R20/1000,"K")
R20 = 150 * 10**3 
print("R20取整 = ",R20/1000,"K")
I_PHO = Vin_AC/R20
print("I_PHO = ",I_PHO*1000,"mA")


print("####################################")
print("#漏电电流采样计算")
print("####################################")
I_leakRangeMax = 18 *10**-3 #漏电电流采样范围
Nps = 500
R5 = 200 #负载电阻
I_leak_s = I_leakRangeMax / Nps
print(" 次级电流 = ",I_leak_s*1000000,"uA")
Usense = I_leak_s * R5
print(" 次级电压 = ",I_leak_s*R5*1000,"mV")

VADC_max = 3.3
Amp_Rat = VADC_max / Usense
Amp_Rat = 100
print(" 放大倍数 = ",Amp_Rat)

R16 = 100 * 10**3 
R18 = R16 / Amp_Rat
print(" R18 = ",R18/1000,"K")

I_leak_ADC = Usense * Amp_Rat
print(" 采样电压 = ",I_leak_ADC*1000,"mV")

print("####################################")
print("#AC电压采样计算")
print("####################################")
R6 = 47 *10**3
R14 = 3.3 *10**3
I_temp = Vin_AC / (R6*6 + R14)

R6_Ploss = I_temp**2 * R6
print("R6功耗 = ",R6_Ploss*1000,"mW")

VAC_IN_ADC = Vin_AC * (R14/(R6*6 + R14))
print(" 采样电压 = ",VAC_IN_ADC*1000,"mV")



print("####################################")
print("#SCR尖峰吸收计算")
print("####################################")
C1 = 2.2 *10**-9
Cx = 1/(2*float(sp.pi)*50*C1)
print("容抗Cx=",Cx/1000,"k")