import matplotlib
import numpy as np
import sympy

class WhiskerModel:
    def __init__(self, E, d, b):
        self.E = E # Young Modulus of PLA in MPa
        self.d = d # diameter in mm
        self.I = np.pi * (d**4) / 64 # Area moment of inertia for a circle
        self.b = b # length of the whisker in mm

    # Initially we need to solve two equations based on simulation/real life data to get the variables in question.
    # Two unknown variables: a (length of virtual base), k (spring constant)
        
    def solve_missing_variables(self, p, delta_a, delta_t):
        A, K = sympy.symbols('A K')
        f1 = (-1*(A**3)/(3*self.E*self.I))*(p-delta_a*K) - (p*(A**2)*self.b/(2*self.E*self.I)) - delta_a
        f2 = (-p*((A+self.b)**3))/(3*self.E*self.I) + (delta_a*K*(A**3))/(3*self.E*self.I) + (delta_a*self.b*K*(A**2))/(2*self.E*self.I) - delta_t
        solution = sympy.nsolve((f1, f2), (A, K), (0.001, 1000))
        self.a = solution[0]
        self.k = solution[1]

        #print(sympy.nsolve((f1, f2), (A, K), (0.001, 100)))
        #equations = [(-1*(A**3)/(3*self.E*self.I))*(p-delta_a*K) - (p*(A**2)*self.b/(2*self.E*self.I)) - delta_a, \
        #             (-p*((A+self.b)**3))/(3*self.E*self.I) + (delta_a*K*(A**3))/(3*self.E*self.I) + (delta_a*self.b*K*(A**2))/(2*self.E*self.I) - delta_t]
        #solutions = sympy.nsolve(equations, A, K, dict=True)
        #print(solutions) 
        
    def deformation_model(self, p):
        d = sympy.Symbol('d')
        sol_d_a = sympy.solve((-1*(self.a**3)/(3*self.E*self.I))*(p-d*self.k) - (p*(self.a**2)*self.b/(2*self.E*self.I)) - d, d, dict=True)
        delta_a = sol_d_a[0][d]
        x = np.linspace(self.a, self.b + self.a, 100)
        delta_x = (-p*x*x*(3*(self.a+self.b)-x))/(6*self.E*self.I) + (delta_a*self.k*(self.a**3))/(3*self.E*self.I) + (delta_a*(x - self.a)*self.k*(self.a**2))/(2*self.E*self.I)
        delta_t = (-p*((self.a+self.b)**3))/(3*self.E*self.I) + (delta_a*self.k*(self.a**3))/(3*self.E*self.I) + (delta_a*self.b*self.k*(self.a**2))/(2*self.E*self.I)


    def draw_whisker(self):
        pts = np.linspace(0, self.b, 100)
        # preds = 

# Define constants:

E = 3500*(10**6)
d = 2*(10**-3)
b = 180*(10**-3)
p = 0.01 # Applied force at the tip
delta_a = 0.03954*(10**-3)
delta_t = 5.0932*(10**-3)

Whisker = WhiskerModel(E, d, b)