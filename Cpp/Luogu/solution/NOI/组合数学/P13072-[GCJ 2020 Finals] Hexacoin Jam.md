# [GCJ 2020 Finals] Hexacoin Jam

## 题目描述

Code Jam 团队的第一种加密货币 **jamcoins** 从未流行起来。今年，我们尝试推出基于 16 进制的 **十六进制币**（$hexacoins$）。要“挖矿”一个 $\mathbf{D}$ 位十六进制币，需要处理恰好 $\mathbf{D}$ 位的 16 进制数（必要时包含前导零）。每个数值代表 $0$ 到 $16^{\mathbf{D}} - 1$（含）之间的整数。16 进制数字由数字 0 到 9 和大写字母 A 到 F 表示。例如，当 $\mathbf{D}=3$ 时，F2B、0C8 和 000 是有效值，对应十进制值 3883、200 和 0。而 1234、DF、C0DE 和 JAM 不是 $\mathbf{D}=3$ 时的有效值。

执行 $\mathbf{D}$ 位 16 进制数加法时，溢出的位数会被丢弃（即模 $16^{\mathbf{D}}$ 加法）。例如，F2B + 0C8 = FF3（十进制 4083），F2B + F2B = E56（十进制 3670，因为和为 7766，模 $16^3$ 得 3670）。

要“挖矿”一个 $\mathbf{D}$ 位十六进制币，计算机需执行以下步骤：

1. 选择一个包含 $\mathbf{N}$ 个 $\mathbf{D}$ 位 16 进制数的列表 $\mathbf{L}$：$\mathbf{L}_1, \mathbf{L}_2, ..., \mathbf{L}_\mathbf{N}$。
2. 选择一个目标范围 $\mathbf{S}$ 到 $\mathbf{E}$（含）的 $\mathbf{D}$ 位 16 进制数。
3. 从所有 16! 种排列中均匀随机选择一个 16 进制数字 0 到 F 的排列 $\mathbf{P}$。
4. 将 $\mathbf{P}$ 应用于 $\mathbf{L}$ 中所有数字的每一位，生成新列表 $\mathbf{L}'$。形式化地，$\mathbf{L}'$ 的第 $i$ 个元素的第 $j$ 位是 $\mathbf{P}$ 作用于 $\mathbf{L}$ 的第 $i$ 个元素的第 $j$ 位的结果。
5. 从 $\mathbf{L}'$ 中均匀随机且独立地选择一对元素（无放回）。
6. 计算所选两个元素的和（丢弃溢出位）。

如果最后一步的和在 $\mathbf{S}$ 到 $\mathbf{E}$（含）之间，则成功挖到一枚十六进制币！例如：

- $\mathbf{L} = [134, 000, FFB, 000, AA9]$。
- $\mathbf{S} = 85C$，$\mathbf{E} = EDF$。
- 计算机选择排列 $\mathbf{P} = (0 \rightarrow 4, 1 \rightarrow A, 2 \rightarrow 2, 3 \rightarrow 8, 4 \rightarrow 9, 5 \rightarrow B, 6 \rightarrow C, 7 \rightarrow 7, 8 \rightarrow F, 9 \rightarrow 1, A \rightarrow 0, B \rightarrow 3, C \rightarrow 5, D \rightarrow 6, E \rightarrow E, F \rightarrow D)$。

应用 $\mathbf{P}$ 后，$\mathbf{L}' = [A89, 444, DD3, 444, 001]$。注意 $\mathbf{S}$ 和 $\mathbf{E}$ 不受 $\mathbf{P}$ 影响。

共有 $(5 \times 4) / 2 = 10$ 对可选，每对概率为 $1/10$。满足范围的求和结果为：A89 + DD3 = 85C、444 + 444 = 888、A89 + 001 = A8A、DD3 + 001 = DD4 和 A89 + 444 = ECD（两次）。

已知前两步的 $\mathbf{L}$ 和范围 $[\mathbf{S}, \mathbf{E}]$，求后续步骤成功挖矿的概率。

## 说明/提示

**样例解释**

样例 #1 中，目标范围仅为 $10$。由于结果末位需为 $0$，且 $\mathbf{P}[0]$ 和 $\mathbf{P}[F]$ 不同，它们的和必须为 $10$（16 进制）。共有 7 对不同的数字满足此条件（不能同为 8），对应 14 种赋值方式。总可能赋值数为 $16 \times 15 = 240$，故概率为 $14/240 = 7/120$。

样例 #2 需额外考虑和为 $11$ 的情况，仅当 $0$ 和 $F$ 被赋值为 $0$ 和 $1$（顺序不限）时成立，概率为 $2/240$。总概率为 $7/120 + 1/120 = 1/15$。

样例 #3 中，无论选择哪对数字，和的末位均为偶数，而目标范围 $FFF$ 为奇数，故概率为 $0$。注意 $0/2$ 不是合法输出，因为 $z$ 未取最小。

**数据范围**

- $2 \leq \mathbf{N} \leq 450$。
- $\mathbf{S}$ 和 $\mathbf{E}$ 均为 $\mathbf{D}$ 位 16 进制数，且 $\mathbf{S} \leq \mathbf{E}$。
- 每个 $\mathbf{L}_i$ 为 $\mathbf{D}$ 位 16 进制数。

**测试集 1（10 分，可见判定）**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{D} \leq 3$。

**测试集 2（10 分，隐藏判定）**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{D} \leq 4$。

**测试集 3（22 分，隐藏判定）**

- $1 \leq \mathbf{T} \leq 10$。
- $2 \leq \mathbf{D} \leq 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 2
10 10
00 FF
2 2
10 11
00 FF
4 3
FFF FFF
230 A10 010 F70
4 3
AFF FFF
230 A10 010 F70```

### 输出

```
Case #1: 7 120
Case #2: 1 15
Case #3: 0 1
Case #4: 2731 8736```

