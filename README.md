# 🔍 LL(1) Parser - FIRST & FOLLOW Computation

---

## 📌 Aim

To compute the **FIRST** and **FOLLOW** sets for a given context-free grammar using C++ and use them as foundational elements in building an **LL(1) parser**.

---

## 🧠 Logic & Mechanism

### 🔹 Definitions

- **FIRST(X)**: The set of terminals that begin the strings derivable from non-terminal `X`.
- **FOLLOW(X)**: The set of terminals that can appear immediately to the right of non-terminal `X` in some "sentential" form.

### 🔄 Algorithm Overview

1. **Input**: Grammar productions in the format `NonTerminal->Production` (e.g., `E->TR`).
2. **FIRST Set Computation**:
   - Recursively compute the FIRST set for each non-terminal.
   - Handle epsilon (`#`) propagation.
3. **FOLLOW Set Computation**:
   - FOLLOW of the start symbol includes `$`.
   - For each production, find positions of non-terminals and evaluate FOLLOW rules using the computed FIRST sets.

### 💡 Notes

- The implementation avoids recomputation by caching already computed FIRST and FOLLOW sets.
- Epsilon (`#`) handling is correctly propagated for nullable non-terminals.

---

## 📥 Sample Input / Output

### 🧾 Input
```yaml
Enter the number of production rules: 3
Enter the production rules:
E->TR
R->+TR
R->#
T->FY
```

### 🖥️ Output
```yaml
First(E) = { ( i }
Follow(E) = { $ ) }

First(R) = { + # }
Follow(R) = { $ ) }

First(T) = { ( i }
Follow(T) = { + $ ) }
```

---

## 🌍 Real-World Applications

- Parser Construction: Core component of LL(1) parsing table generation.
- Compiler Design: Assists in syntax analysis of source code.
- Syntax Checking: Ensures source code adheres to grammar rules.
- Language Development: Useful in designing domain-specific languages (DSLs).

---
  
