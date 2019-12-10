---
marp: true
---

# Matrix multiplication Analysis

By: Shubham Arora

---
# Algorithms Compared

- Naive
- Strassens' algorithm
<!-- - Coppersmith–Winograd algorithm
- Standard c++ implementations
  - tensorflow::ops::MatMul
  - boost::ublas -->
---

<!-- # Matrices
- Desnse matrices
- Sparse matrices

*Maybe compare parallel performance on GPU?* -->

# Naive Matrix 


For two matrices *a* and *b* that can be multiplied 


![](vanilla-formula.jpg)


---

# Naive Matrix multiplication

For two matrices of size n x n

Time complexity: O(n^3)

---

# Strassens's Method of Matrix Multiplication

## Key insight
 - Multiplication is computationally more expensive than addition
 - Utilise Dynamic programming 


---
# Preparation for Dynamic programming
Let us break down the problem into subparts as:
![](strassen-mat-break.jpg)

---

# Naive Algorithm

Now, the standard algorithm does the follows: 

![](mat-break-naive.jpg)

i.e. 8 multiplications, 4 Additions


---

# Strassens's Algorithm

Strassen's algorithm does a neat trick: 

![](strassen-mat-break-1.jpg) ![](strassen-mat-break-2.jpg)

i.e. **7 multiplications**, 18 Additions

---

# Strassen Algorithm

For two matrices of size n x n

Time complexity: O(n^lg(7)) = O(n^2.81)


---

# Results


---
# Some notes

 - Current fastest algorithms has performance : 
 - However, they have  a very large overhead, and not used currently in practice
 - The lower bound on Matrix Multiplication is proved to be: O(n^2)
