Copyright Szabo Cristina-Andreea 2022-2023

# Octave Simulator

# **Octave Simulator**

This project is a simulation of matrix operations commonly found in **Octave** implemented in C. It supports various matrix operations such as addition, multiplication, transposition, and more, all through user input. The operations are handled with dynamic memory allocation, ensuring flexibility and memory efficiency.

## **Features**
- **Dynamic Matrix Management**: Supports adding, removing, and resizing matrices dynamically.
- **Matrix Operations**:
  - Matrix addition and subtraction
  - Matrix multiplication
  - Matrix transposition
  - Matrix exponentiation (raising matrices to a power)
  - Matrix multiplication using **Strassen's Algorithm**
- **Operations Handling**: A set of operations that can be applied to matrices through user interaction, including:
  - Load matrices
  - Display matrix dimensions
  - Print matrix
  - Multiply matrices
  - Transpose matrices
  - Sort matrices by their sum
  - Resize matrices
  - Raise matrices to a power
  - Free matrix memory
  
## **Operations**
Here is a brief overview of the operations supported in the simulator:

1. **L (Load Matrix)**:
   - Load a new matrix into memory with dynamic allocation.
   - Matrices are stored with an index, and their dimensions and sums are tracked.

2. **D (Dimensions)**:
   - Displays the dimensions of the matrix specified by its index.

3. **P (Print Matrix)**:
   - Displays the matrix corresponding to a given index.

4. **C (Resize Matrix)**:
   - Resize a matrix by selecting specific rows and columns for inclusion.

5. **M (Matrix Multiplication)**:
   - Multiplies two matrices if their dimensions allow it.
   - New matrix is created with the result.

6. **O (Sort Matrices)**:
   - Sort matrices based on the sum of their elements in ascending order.

7. **T (Transpose Matrix)**:
   - Computes the transpose of a matrix.

8. **R (Matrix Exponentiation)**:
   - Raises a matrix to a power.

9. **F (Free Matrix)**:
   - Frees the memory occupied by a specified matrix.

10. **S (Strassen's Matrix Multiplication)**:
    - Performs matrix multiplication using **Strassen's Algorithm** for efficient computation.

11. **Q (Quit)**:
    - Frees all allocated memory and terminates the program.

   ## **Memory Management**
- **Dynamic Allocation**: Memory for matrices is allocated dynamically using `malloc` and `realloc` functions. Proper memory deallocation is performed when matrices are no longer needed to avoid memory leaks.
- **Defensive Programming**: Checks are in place to ensure that operations are only performed on valid matrices (e.g., checking dimensions before multiplication).
