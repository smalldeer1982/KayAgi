# 题目信息

# [NOIP 2012 提高组] Vigenère 密码

## 题目描述

16 世纪法国外交家 Blaise de Vigenère 设计了一种多表密码加密算法 Vigenère 密码。Vigenère 密码的加密解密算法简单易用，且破译难度比较高，曾在美国南北战争中为南军所广泛使用。

 
在密码学中，我们称需要加密的信息为明文，用 $M$ 表示；称加密后的信息为密文，用 $C$ 表示；而密钥是一种参数，是将明文转换为密文或将密文转换为明文的算法中输入的数据，记为 $k$。在 Vigenère 密码中，密钥 $k$ 是一个字母串，$k=k_1,k_2,…,k_n$。当明文 $M=m_1,m_2,…,m_n$ 时，得到的密文 $C=c_1,c_2,…,c_n$，其中 $c_i$=$m_i \operatorname{\circledR} k_i$，运算 $\circledR$ 的规则如下表所示：

$$\begin{array}{c|cccccccccccccccccccccccccc}
\circledR &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt}  \\\hline
\tt A &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt}  \\
\tt B &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt}  \\
\tt C &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt}  \\
\tt D &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt}  \\
\tt E &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt}  \\
\tt F &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt}  \\
\tt G &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt}  \\
\tt H &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt}  \\
\tt I &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt}  \\
\tt J &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt}  \\
\tt K &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt}  \\
\tt L &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt}  \\
\tt M &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt}  \\
\tt N &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt}  \\
\tt O &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt}  \\
\tt P &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt}  \\
\tt Q &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt}  \\
\tt R &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt}  \\
\tt S &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt}  \\
\tt T &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt}  \\
\tt U &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt}  \\
\tt V &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt}  \\
\tt W &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt}  \\
\tt X &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt}  \\
\tt Y &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt}  \\
\tt Z &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt}  \\

\end{array}
$$

Vigenère 加密在操作时需要注意：

1. $\circledR$ 运算忽略参与运算的字母的大小写，并保持字母在明文 $M$ 中的大小写形式；
2. 当明文 $M$ 的长度大于密钥 $k$ 的长度时，将密钥 $k$ 重复使用。

例如，明文 $M=\texttt{Helloworld}$，密钥 $k=\texttt{abc}$ 时，密文 $C=\texttt{Hfnlpyosnd}$。

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|c|c|c|c|c|c|c|c|} \hline
\textsf{明文} & \tt H & \tt e & \tt l & \tt l & \tt o & \tt w & \tt o & \tt r & \tt l & \tt d \\  \hline
\textsf{密钥} & \tt a & \tt b & \tt c & \tt a & \tt b & \tt c & \tt a & \tt b & \tt c & \tt a \\  \hline
\textsf{密文} & \tt H & \tt f & \tt n & \tt l & \tt p & \tt y & \tt o & \tt s & \tt n & \tt d \\  \hline
\end{array}
$$


## 说明/提示

对于 $100\%$ 的数据，输入的密钥的长度不超过 $100$，输入的密文的长度不超过 $1000$，且都仅包含英文字母。

NOIP 2012 提高组 第一天 第一题

## 样例 #1

### 输入

```
CompleteVictory
Yvqgpxaimmklongnzfwpvxmniytm```

### 输出

```
Wherethereisawillthereisaway```

# AI分析结果

# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（字符串处理+模运算+循环逻辑）


🗣️ **初步分析**：  
这道题就像一个“字符串解码游戏”——给定一把“密钥钥匙”和一串“密文锁”，我们需要用钥匙的“偏移量”逆推打开锁的“明文密码”。核心逻辑是**字符转换+循环密钥+模运算**：  
- **字符转换**：将字母（大小写）转为数字（比如`a`/`A`→0，`b`/`B`→1，…，`z`/`Z`→25），方便计算。  
- **循环密钥**：当密文比密钥长时，密钥要像“传送带”一样循环使用（比如密钥是`abc`，密文第4个字符用`a`，第5个用`b`）。  
- **模运算**：处理字母“绕圈”问题（比如`A`减1应该变成`Z`，用`(x - y + 26) % 26`避免负数）。  

**核心算法流程**：  
1. 读取密钥和密文。  
2. 遍历密文的每个字符：  
   - 取密钥的当前字符（循环使用，用`i % key_len`）。  
   - 将两者转为数字（忽略大小写），计算`(密文数字 - 密钥数字 + 26) % 26`，得到明文数字。  
   - 将明文数字转回字符（保持密文的大小写）。  
3. 输出明文。  

**可视化设计思路**：  
用8位像素风格展示“解码流水线”：  
- 左边是密文字符串（像素块，比如`H`是蓝色），中间是密钥字符串（循环滚动，当前用的`a`高亮黄色），右边是明文字符串（待生成的灰色块）。  
- 每处理一个字符，密文块闪烁，密钥块弹出“偏移量”（比如`a`→0），计算过程用像素文字显示（`H(7) - a(0) = 7 → G`），然后明文块变成绿色（`G`），伴随“叮”的音效。  
- 循环密钥时，密钥字符串像“跑马灯”一样滚动，提示“接下来用下一个钥匙”。  


## 2. 精选优质题解参考

### 题解一：（来源：ingu，赞：472）  
* **点评**：这道题解的代码堪称“简洁天花板”！作者用了一个巧妙的ASCII技巧——`x & 31`（取字符二进制后5位），直接得到字母在字母表中的顺序（`A`/`a`→1，`B`/`b`→2，…，`Z`/`z`→26），省去了判断大小写的麻烦。循环部分用`i % k.length()`处理密钥循环，计算时用`(c[i] & 31) - t`，如果结果≤0就加26，完美处理了“绕圈”问题。代码只有10行，却覆盖了所有逻辑，非常适合学习“如何用位运算简化字符处理”。


### 题解二：（来源：Sinwind，赞：3）  
* **点评**：这道题解的结构非常清晰，作者把解密逻辑封装成了`decryption`函数，输入密文和密钥字符，输出明文。函数里用`toupper`统一转换大小写，计算时用`(temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k)`，逻辑直白。主函数里用`i % key_len`循环密钥，代码可读性很高，适合学习“函数封装”和“逻辑分层”。


### 题解三：（来源：ShirasuAzusaSaikou，赞：2）  
* **点评**：这道题解的思路很“接地气”，作者直接指出“这题就是算偏移”，然后用`tolower`统一密钥的大小写，避免了复杂的条件判断。循环部分用`ki = (ki + 1) % kl`处理密钥循环，计算时用`(tolower(m[i]) - k[ki] + 26) % 26`，再根据密文的大小写添加`a`或`A`。代码简洁易懂，适合学习“如何简化条件判断”。


## 3. 核心难点辨析与解题策略

### 1. **难点1：字母与数字的转换（如何处理大小写？）**  
* **问题**：密文和密钥有大小写，如何统一计算？  
* **解决策略**：将字母转为数字时，忽略大小写（比如`a`和`A`都转为0，`b`和`B`都转为1）。计算完成后，再根据密文的大小写转回字符（比如密文是大写，明文就用`A`+数字；密文是小写，就用`a`+数字）。  
* 💡 **学习笔记**：大小写转换的关键是“统一计算，保留原始大小写”。


### 2. **难点2：循环使用密钥（如何处理密钥长度不足？）**  
* **问题**：当密文比密钥长时，如何重复使用密钥？  
* **解决策略**：用模运算`i % key_len`（`i`是密文的当前索引，`key_len`是密钥长度）。比如密钥长度是3，`i=3`时，`3%3=0`，用密钥的第0个字符；`i=4`时，`4%3=1`，用第1个字符，以此类推。  
* 💡 **学习笔记**：模运算就是“循环计数器”，能帮你重复使用有限的资源。


### 3. **难点3：模运算处理负数（如何避免“绕圈”错误？）**  
* **问题**：当密文数字小于密钥数字时（比如密文是`A`→0，密钥是`B`→1），`0-1=-1`，直接取模会得到负数，无法对应字母。  
* **解决策略**：计算时加26再取模，即`(密文数字 - 密钥数字 + 26) % 26`。比如`0-1+26=25`，`25%26=25`，对应`Z`，正好是正确结果。  
* 💡 **学习笔记**：加26是为了“补满一圈”，确保结果是非负数。


### ✨ 解题技巧总结  
- **位运算简化字符处理**：用`x & 31`可以快速得到字母顺序（适用于`A`-`Z`和`a`-`z`）。  
- **函数封装**：将解密逻辑写成函数，让代码更清晰、易维护。  
- **统一大小写**：用`tolower`或`toupper`统一密钥的大小写，减少条件判断。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：综合了ingu、Sinwind、ShirasuAzusaSaikou的思路，兼顾简洁性和可读性。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  #include <cctype> // 包含tolower函数

  using namespace std;

  int main() {
      string key, cipher;
      cin >> key >> cipher;
      int key_len = key.size();
      // 统一密钥为小写（简化判断）
      for (char &c : key) {
          c = tolower(c);
      }
      // 处理每个密文字符
      for (int i = 0; i < cipher.size(); ++i) {
          char c = cipher[i];
          char k = key[i % key_len]; // 循环使用密钥
          // 将密文和密钥转为数字（0-25）
          int c_num = tolower(c) - 'a';
          int k_num = k - 'a';
          // 计算明文数字（处理负数）
          int m_num = (c_num - k_num + 26) % 26;
          // 转回字符（保持密文大小写）
          char m = isupper(c) ? ('A' + m_num) : ('a' + m_num);
          cout << m;
      }
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取密钥和密文。  
  2. 将密钥统一转为小写（避免判断密钥的大小写）。  
  3. 遍历密文的每个字符：  
     - 取密钥的当前字符（用`i % key_len`循环）。  
     - 将密文和密钥转为0-25的数字（用`tolower`统一密文的大小写）。  
     - 计算明文数字（`(c_num - k_num + 26) % 26`）。  
     - 将明文数字转回字符（用`isupper`判断密文的大小写，保持一致）。  
  4. 输出明文。  


### 针对各优质题解的片段赏析  

#### 题解一（来源：ingu）  
* **亮点**：用位运算`&31`快速获取字母顺序，代码极短。  
* **核心代码片段**：  
  ```cpp
  for (int i = 0; i < c.length(); i++) {
      int t = (k[i % k.length()] & 31) - 1;
      c[i] = (c[i] & 31) - t > 0 ? c[i] - t : c[i] - t + 26;
  }
  ```  
* **代码解读**：  
  - `k[i % k.length()] & 31`：取密钥字符的后5位，得到1-26的顺序（`A`/`a`→1，`B`/`b`→2）。减1后得到0-25的偏移量（`t`）。  
  - `c[i] & 31`：取密文字符的后5位，得到1-26的顺序。减`t`后，如果结果>0，直接减`t`；否则加26（处理绕圈）。  
  - 最后将结果赋给`c[i]`，因为`c[i]`的大小写没有变（`&31`不影响大小写位），所以直接输出即可。  
* 💡 **学习笔记**：位运算可以快速处理字符的“类别”信息（比如字母顺序），节省代码量。


#### 题解二（来源：Sinwind）  
* **亮点**：函数封装，逻辑清晰。  
* **核心代码片段**：  
  ```cpp
  char decryption(char c, char k) {
      char temp_c = toupper(c);
      char temp_k = toupper(k);
      char m = isupper(c) ? 'A' : 'a';
      m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
      return m;
  }
  ```  
* **代码解读**：  
  - `toupper(c)`和`toupper(k)`：将密文和密钥转为大写，统一计算。  
  - `isupper(c) ? 'A' : 'a'`：确定明文的大小写（和密文一致）。  
  - `(temp_c >= temp_k) ? ... : ...`：如果密文数字≥密钥数字，直接减；否则加26再减（处理绕圈）。  
* 💡 **学习笔记**：函数封装能将复杂逻辑拆分成小模块，让代码更易读、易调试。


#### 题解三（来源：ShirasuAzusaSaikou）  
* **亮点**：用`tolower`统一密钥，简化判断。  
* **核心代码片段**：  
  ```cpp
  for (auto &i : k) i = tolower(i); // 统一密钥为小写
  for (int i = 0; i < ml; i++) {
      cout << (char)(((m[i] >= 'a') ? 'a' : 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
      ki = (ki + 1) % kl; // 循环密钥
  }
  ```  
* **代码解读**：  
  - `for (auto &i : k) i = tolower(i)`：将密钥统一转为小写，避免后续判断密钥的大小写。  
  - `tolower(m[i]) - k[ki]`：将密文转为小写，减去密钥的小写字符（得到偏移量）。  
  - `(tolower(m[i]) - k[ki] + 26) % 26`：处理负数，得到0-25的明文数字。  
  - `(m[i] >= 'a') ? 'a' : 'A'`：确定明文的大小写（和密文一致）。  
* 💡 **学习笔记**：统一变量的“状态”（比如大小写），可以减少条件判断，让代码更简洁。  


## 5. 算法可视化：像素动画演示（核心部分）

### 动画演示主题：《像素解码师》  
（仿FC红白机风格，背景是复古的电脑屏幕，上面有三个字符串：密文、密钥、明文）


### 核心演示内容  
1. **初始化场景**：  
   - 左边是密文字符串（比如`Helloworld`），每个字符是蓝色像素块。  
   - 中间是密钥字符串（比如`abc`），每个字符是黄色像素块，循环滚动（比如`a`→`b`→`c`→`a`）。  
   - 右边是明文字符串（待生成），每个字符是灰色像素块。  
   - 底部有控制面板：“单步”（红色按钮）、“自动”（绿色按钮）、“重置”（蓝色按钮）、速度滑块（1-5档）。  

2. **单步执行**：  
   - 选中密文的第一个字符（`H`），闪烁红色。  
   - 选中密钥的第一个字符（`a`），闪烁黄色，旁边弹出文字“偏移量：0”。  
   - 计算过程：`H`→`h`（小写）→7（`h`-`a`=7），`a`→0，`7-0=7`→`g`（`a`+7）。  
   - 明文的第一个字符变成绿色（`G`），伴随“叮”的音效。  
   - 密钥滚动到下一个字符（`b`）。  

3. **自动播放**：  
   - 按照单步的逻辑，依次处理所有密文字符，速度由滑块控制（1档最慢，5档最快）。  
   - 处理完所有字符后，明文字符串闪烁绿色，伴随“胜利”音效（比如FC游戏的通关音乐）。  

4. **重置**：  
   - 密文、密钥、明文恢复初始状态，控制面板重置。  


### 设计思路  
- **像素风格**：用8位像素块表示字符，符合复古游戏的感觉，让学习者觉得“有趣”。  
- **高亮与音效**：通过闪烁和音效突出当前操作，帮助学习者聚焦“关键步骤”（比如密文、密钥的当前字符，计算过程）。  
- **循环密钥动画**：用滚动的方式展示密钥的循环使用，让学习者直观理解“i%key_len”的作用。  


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移  
本题的核心技巧（字符串处理+模运算+循环逻辑）可以用到以下场景：  
- **密码学**：比如凯撒密码（单字符偏移）、维吉尼亚密码（多字符偏移）的解密。  
- **字符串转换**：比如将字符串转为数字（比如`"ABC"`→`012`），或反之。  
- **循环逻辑**：比如处理循环队列、循环数组等数据结构。  


### 练习推荐（洛谷）  
1. **洛谷 P1088** - 火星人  
   * 🗣️ **推荐理由**：需要处理字符串的循环移位，类似本题的“循环密钥”逻辑，能巩固模运算的应用。  
2. **洛谷 P1125** - 笨小猴  
   * 🗣️ **推荐理由**：需要统计字符串中的字母频率，涉及字符转换（字母→数字），能巩固字符处理技巧。  
3. **洛谷 P1200** - [USACO1.1]你的飞碟在这儿Your Ride Is Here  
   * 🗣️ **推荐理由**：需要将字符串转为数字（每个字符的ASCII码乘积），并进行模运算，类似本题的“字符→数字→模运算”流程。  


## 7. 学习心得与经验分享（若有）

### 参考经验（来自ingu）  
> “我用了`x & 31`来获取字母顺序，因为`A`和`a`的二进制后5位是相同的，这样可以省去判断大小写的麻烦。”  
* **点评**：这个技巧非常实用！位运算能快速处理字符的“类别”信息（比如字母顺序），比`if`判断更高效、更简洁。下次遇到字符处理问题时，不妨想想“有没有位运算的技巧？”。


### 参考经验（来自Sinwind）  
> “我把解密逻辑写成了函数，这样主函数看起来更清晰，也方便调试。”  
* **点评**：函数封装是编程的重要技巧之一。将复杂逻辑拆分成小函数，不仅能让代码更易读，还能提高代码的复用性（比如下次遇到类似的解密问题，可以直接用这个函数）。


## 结语  
本次关于“Vigenère密码”的C++解题分析就到这里。希望这份指南能帮助你掌握字符串处理、模运算和循环逻辑的技巧。记住：编程的关键是“拆解问题+找规律+用技巧”，多练习、多思考，你一定会越来越厉害！💪  

下次我们再一起探索新的编程挑战吧！😊

---
处理用时：241.96秒