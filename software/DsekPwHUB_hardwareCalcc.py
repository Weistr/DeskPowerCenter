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


XT30_CN1_CurrMax = 15#XT30端子电流
  
print("####################################")
print("#采样电阻计算")
print("####################################")

Rsense_Ploss = 1.5
Rsense = Rsense_Ploss / XT30_CN1_CurrMax**2
print("Rsense = ",Rsense*1000,"mR")
Rsense = 0.006
print("取整Rsense = ",Rsense,"mR")
Udrop_Rsense = sp.sqrt(Rsense_Ploss * Rsense)
print("Rsense Voltage = ",Udrop_Rsense*1000,"mV")





print("####################################")
print("#12V ADC采样电阻计算（最高支持24V）")
print("####################################")
VsmpMax = 27 #留余量
VadcMax = 3.3
Rh = 11 *10**3
# 
Rl = None
VARIABLES = {
    'VsmpMax': VsmpMax,
    'VadcMax': VadcMax,
    'Rh': Rh,
    'Rl': Rl,
}
EQUATIONS = [
    "VsmpMax = VadcMax/Rl * (Rl+Rh)"
]
solve_equations(EQUATIONS,VARIABLES)
print("Rl=",Rl/1000,"k")
Rl = 1.5*10**3
print("Rl取整=",Rl/1000,"k")
I_temp = VsmpMax/(Rl+Rh)
P_Rl = I_temp**2 * Rl
P_Rh = I_temp**2 * Rh
print("Rh功耗 = ",P_Rh*1000,"mW")
print("Rl功耗 = ",P_Rl*1000,"mW")




print("####################################")
print("#5V ADC采样电阻计算")
print("####################################")
VsmpMax = 6 #留余量
Rh = 5.6 *10**3
Rl = None
VARIABLES = {
    'VsmpMax': VsmpMax,
    'VadcMax': VadcMax,
    'Rh': Rh,
    'Rl': Rl,
}
EQUATIONS = [
    "VsmpMax = VadcMax/Rl * (Rl+Rh)"
]
solve_equations(EQUATIONS,VARIABLES)
print("Rl=",Rl/1000,"k")
Rl = 6.8*10**3
print("Rl取整=",Rl/1000,"k")
I_temp = VsmpMax/(Rl+Rh)
P_Rl = I_temp**2 * Rl
P_Rh = I_temp**2 * Rh
print("Rh功耗 = ",P_Rh*1000,"mW")
print("Rl功耗 = ",P_Rl*1000,"mW")
