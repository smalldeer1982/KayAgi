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
\def\arraystretch{1.5}
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



---
# 💡 Kay的C++算法解析：Vigenère 密码解密 深入学习指南 💡

<introduction>
今天我们来一起分析“Vigenère 密码解密”这道题。Vigenère 密码是一种经典的多表加密算法，解密过程需要结合密钥循环使用和字符位移的逆向计算。本指南将帮助你理解核心逻辑，掌握解题技巧，并通过可视化演示直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（侧重字符串处理、模运算及循环密钥的使用）

🗣️ **初步分析**：
Vigenère 密码的解密问题，本质是“已知密文和密钥，逆向计算明文”。核心在于理解加密时的位移规则，并通过模运算逆向推导。  
简单来说，加密时每个明文字符会根据密钥对应位置的字符进行循环右移（例如密钥是 'B'，则明文右移1位），解密则是左移相同位数。由于字母表是循环的（A的左边是Z），需要用模运算（`(x + 26) % 26`）处理越界问题。

- **题解思路**：所有题解均围绕“字符转数字→计算明文数字→转回字符”展开。差异主要在于数字转换的具体实现（如用 `c - 'A'` 还是 `c & 31`）和循环密钥的处理（模运算或手动循环）。
- **核心难点**：如何正确计算明文数字（避免负数）、保持原字符的大小写、循环使用密钥。
- **可视化设计**：用8位像素风展示密文、密钥的逐个字符，动态演示“字符→数字→计算→明文”的过程，高亮密钥循环（如密钥用完时“弹回”开头）、数字计算（如减法后加26再取模）等关键步骤。动画中会有“叮”的音效提示每个字符处理完成，完成所有解密时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下3道题解因逻辑简洁、代码易读且高效，被选为优质参考：
</eval_intro>

**题解一：作者：ingu (赞：479)**
* **点评**：此题解用位运算巧妙简化ASCII处理，代码极短但逻辑清晰。作者利用 `c & 31` 直接获取字母在字母表中的位置（A-Z对应1-26），避免了复杂的大小写判断。循环密钥通过 `i % k.length()` 实现，简洁高效。代码对边界条件（如减法后负数）的处理（`c[i]-t>0?c[i]-t:c[i]-t+26`）直接且正确，非常适合竞赛场景。

**题解二：作者：Sinwind (赞：3)**
* **点评**：此题解结构清晰，将核心逻辑封装为 `decryption` 函数，提高了可读性。通过 `toupper` 统一处理大小写，再根据原字符的大小写决定结果的大小写，逻辑直观。循环密钥的处理（`i % key_len`）和模运算的应用（`(temp_c + 26 - temp_k)`）均符合标准解法，适合新手理解。

**题解三：作者：qhr2023 (赞：3)**
* **点评**：此题解用更数学化的方式推导公式，直接通过 `(c - k + 26) % 26` 计算明文数字，代码简洁。虽然未显式处理大小写（通过条件判断直接返回对应大小写的字符），但逻辑正确且高效。适合理解模运算的核心作用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决Vigenère解密问题时，以下3个关键点需要特别注意：
</difficulty_intro>

1.  **关键点1：循环密钥的正确使用**  
    * **分析**：当密文长度大于密钥长度时，密钥需要重复使用（如密文第4位对应密钥第1位）。优质题解普遍使用 `i % key_len` 实现循环（`i`是密文当前索引，`key_len`是密钥长度），例如 `k[i % k.length()]`。  
    * 💡 **学习笔记**：模运算 `%` 是处理循环问题的“神器”，记住 `i % n` 能让 `i` 在 `0~n-1` 范围内循环。

2.  **关键点2：避免减法后出现负数**  
    * **分析**：密文字母数字（如A=0）减去密钥字母数字（如B=1）可能得到负数（如A-B= -1），需要加26再取模。例如 `(c_num - k_num + 26) % 26` 能确保结果在 `0~25` 之间。  
    * 💡 **学习笔记**：模运算前加26是为了抵消负数，确保结果非负。

3.  **关键点3：保持原字符的大小写**  
    * **分析**：明文的大小写与密文一致（如密文是小写，明文也小写）。优质题解通过判断密文字符的大小写（`isupper(c)` 或直接比较ASCII码），决定结果的基准字符（`'A'` 或 `'a'`）。  
    * 💡 **学习笔记**：保持大小写只需记录密文字符的大小写状态，结果字符的基准（`'A'`或`'a'`）与密文一致。

### ✨ 解题技巧总结
- **字符转数字**：用 `c - 'A'`（大写）或 `c - 'a'`（小写）将字符转为0-25的数字，简化计算。  
- **模运算统一处理**：无论是否越界，用 `(x + 26) % 26` 确保结果在合法范围内。  
- **循环密钥**：用 `i % key_len` 实现密钥的循环使用，简洁高效。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，代码简洁且覆盖所有关键点：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了ingu和Sinwind的思路，用模运算处理循环密钥和越界问题，保持原字符大小写。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    char decrypt_char(char c, char key_char) {
        bool is_upper = isupper(c);  // 记录密文的大小写
        int c_num = tolower(c) - 'a';  // 转为0-25的数字（统一小写）
        int key_num = tolower(key_char) - 'a';  // 密钥转为0-25的数字
        int plain_num = (c_num - key_num + 26) % 26;  // 计算明文数字（加26防负）
        return is_upper ? plain_num + 'A' : plain_num + 'a';  // 恢复原大小写
    }

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        int key_len = key.size();
        for (int i = 0; i < cipher.size(); ++i) {
            char current_key = key[i % key_len];  // 循环使用密钥
            cout << decrypt_char(cipher[i], current_key);
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取密钥和密文，然后逐个处理密文字符。`decrypt_char` 函数负责将单个密文字符和对应密钥字符转换为明文：通过 `tolower` 统一处理大小写，计算明文数字后恢复原大小写。主函数中用 `i % key_len` 实现密钥的循环使用。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：作者：ingu**
* **亮点**：用位运算 `c & 31` 直接获取字母位置（A-Z对应1-26），简化ASCII处理。
* **核心代码片段**：
    ```cpp
    int t=(k[i%k.length()]&31)-1;  // 密钥转为0-25（A对应0）
    c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;  // 计算明文（直接操作ASCII码）
    ```
* **代码解读**：  
  `k[i%k.length()]&31` 利用位运算（31是二进制11111）提取字母的后5位，得到A-Z的1-26，减1后转为0-25。`c[i]&31` 同理得到密文字母的1-26，减去密钥数字后，若结果>0则直接用，否则加26（如A-1=Z）。此方法避免了显式的大小写判断，利用ASCII码的特性简化代码。
* 💡 **学习笔记**：位运算可以高效处理字符的字母位置提取，但需注意ASCII码的规律（大写和小写字母的后5位相同）。

**题解二：作者：Sinwind**
* **亮点**：将解密逻辑封装为函数，结构清晰，适合模块化编程。
* **核心代码片段**：
    ```cpp
    char decryption(char c, char k) {
        char temp_c = toupper(c);  // 统一转大写
        char temp_k = toupper(k);  // 统一转大写
        char m = (isupper(c)) ? 'A' : 'a';  // 原字符的大小写
        m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
        return m;
    }
    ```
* **代码解读**：  
  函数先将密文和密钥字符统一转大写，计算位移差（若密文数字≥密钥数字，直接减；否则加26再减），最后根据原字符的大小写（`isupper(c)`）决定结果是大写还是小写。此方法逻辑直白，适合新手理解。
* 💡 **学习笔记**：函数封装能提高代码可读性，尤其在复杂逻辑中。

**题解三：作者：qhr2023**
* **亮点**：用数学公式直接计算，代码极简。
* **核心代码片段**：
    ```cpp
    char m (char k, char c) {
        if (k>='a'&&c>='a') return (c-k+26)%26+'a';
        else if (k>='a'&&c<='Z') return (c-'A'-k+'a'+26)%26+'A';
        else if (k<='Z'&&c>='a') return (c-'a'-k+'A'+26)%26+'a';
        else return (c-k+26)%26+'A';
    }
    ```
* **代码解读**：  
  函数根据密文和密钥的大小写组合（4种情况），分别计算明文。例如，当密文和密钥都是小写时，直接用 `(c - k + 26) % 26 + 'a'` 计算。此方法虽需处理多种情况，但公式统一，适合快速实现。
* 💡 **学习笔记**：分情况讨论能清晰处理不同输入条件，但需确保覆盖所有可能。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解解密过程，我们设计一个“像素密码探险”动画，用8位像素风格展示每个字符的解密步骤！
</visualization_intro>

  * **动画演示主题**：`像素密码探险——Vigenère解密大作战`
  * **核心演示内容**：展示密文字符串、密钥字符串，逐个处理每个密文字符：  
    1. 密钥循环：当密钥用完时，用“弹回”动画（如密钥字符从末尾跳回开头）。  
    2. 字符转数字：密文和密钥字符变成数字（如'A'→0，'B'→1），用像素数字显示。  
    3. 计算明文数字：用箭头连接密文数字和密钥数字，显示减法过程（如5-2=3，或5-7=-2→-2+26=24）。  
    4. 转回字符：数字变回字符，保持原大小写（如数字3→'D'或'd'）。

  * **设计思路简述**：  
    8位像素风（如FC游戏画面）降低学习压力，动态数字转换和箭头动画突出关键步骤。音效（如“叮”提示字符处理完成）强化操作记忆，循环密钥的“弹回”动画直观展示模运算效果。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：  
       - 屏幕分为三行：顶部是密文（像素字母），中间是密钥（像素字母），底部是明文（初始为空）。  
       - 控制面板有“单步”“自动播放”“调速”按钮，背景播放8位风格BGM。
    2. **处理第i个密文字符**：  
       - 密文第i个字符（如'Y'）和密钥第i%key_len个字符（如'v'）高亮（黄色边框）。  
       - 字符变数字：'Y'→24（大写），'v'→21（小写转大写后21），数字用像素块显示。  
       - 计算明文数字：24-21=3（显示减法箭头），结果3→'D'（保持大写）。  
       - 明文底部添加'D'，伴随“叮”音效。  
    3. **密钥循环演示**：  
       - 当i=key_len时（如密钥长度3，i=3），密钥字符从第3个（超出长度）“弹回”第0个（如第3个位置显示“→0”箭头）。  
    4. **完成所有解密**：  
       - 明文全部生成，播放胜利音效（欢快的8位音乐），所有字符闪烁庆祝。

  * **旁白提示**：  
    - “看！密文的'Y'和密钥的'v'正在配对~”  
    - “'Y'转数字是24，'v'转数字是21，24-21=3，所以明文是'D'！”  
    - “密钥用完啦，我们跳回开头继续用~”

<visualization_conclusion>
通过这个动画，你可以直观看到每个字符的解密过程，理解循环密钥和模运算的作用！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环位移+模运算”，这种思路还能解决许多字符串加密问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - **凯撒密码**：固定位移的单表加密（如所有字母右移3位），解密是左移3位，可用类似模运算处理。  
    - **替换密码**：用固定映射表替换字母，解密需反向映射，核心是字符替换的逆向操作。  
    - **栅栏密码**：将字符按行排列后按列读取，解密需恢复原排列，核心是分块和重组。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1328 生活大爆炸版石头剪刀布**  
        * 🗣️ **推荐理由**：需要处理循环规则（类似密钥循环），用模运算计算结果，巩固循环逻辑。  
    2.  **洛谷 P1914 小书童——密码**  
        * 🗣️ **推荐理由**：基础凯撒密码解密，练习字符位移和模运算的应用。  
    3.  **洛谷 P2758 编辑距离**  
        * 🗣️ **推荐理由**：字符串处理的进阶题，练习动态规划和字符操作，提升综合能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者提到调试时遇到的问题，例如：
</insights_intro>

> **参考经验 (来自 123456Zhe)**：“在处理小写字母减密钥时，一开始没考虑越界（如'a'-1会变成'`'），后来通过加26再取模解决了。”

**点评**：这是常见的边界问题！处理字符位移时，一定要考虑越界情况（如'A'-1应回到'Z'）。模运算（`(x + 26) % 26`）是解决此类问题的通用方法，能确保结果始终在合法范围内。

-----

<conclusion>
通过本指南，你已经掌握了Vigenère密码解密的核心逻辑、代码实现和可视化过程。记住，多练习类似题目（如凯撒密码、替换密码）能巩固这些技巧。下次遇到字符串加密问题，你一定能轻松解决！💪
</conclusion>

---
处理用时：156.87秒