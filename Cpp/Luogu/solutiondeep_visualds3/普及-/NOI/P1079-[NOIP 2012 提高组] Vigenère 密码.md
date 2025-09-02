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
# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡

<introduction>
  今天我们来一起破解“Vigenère密码”这道经典的字符串处理题！它曾是NOIP2012提高组的第一道题，核心是**字符串的加密逆运算**——给定密文和密钥，还原出明文。本指南会帮你理清规则、掌握关键技巧，还会用像素动画让你“看”到解密的每一步~
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理 + 编程技巧应用`

🗣️ **初步分析**：
> 解决Vigenère密码，关键是理解“**字母的循环偏移**”——就像字母表是一个环形跑道（A→B→…→Z→A）：加密时，明文字母沿着跑道往前跑`k_i`步变成密文；解密时，密文字母要**往回跑`k_i`步**变回明文。而密钥`k`是“跑步的步数表”，如果密文比密钥长，就循环用这个表（比如密钥是`abc`，密文第4位用`a`，第5位用`b`，依此类推）。

   - **题解核心思路**：所有题解的本质都是“**将字符转成数字计算，再转回字符**”——把A-Z映射成0-25（或1-26），用公式`明文数字 = (密文数字 - 密钥数字 + 26) % 26`（加26是防止负数），最后根据密文的大小写恢复明文的大小写。
   - **核心难点**：① 如何统一处理大小写？② 如何循环使用密钥？③ 如何避免偏移时“跑过界”？
   - **解决方案**：用ASCII码将字母转成数字（比如`c - 'A'`或`c - 'a'`），用`i % 密钥长度`循环密钥，用`(x + 26) % 26`处理边界。
   - **可视化设计思路**：我会设计一个8位像素动画——屏幕上有三排像素块：左边是**密文块**（红色），中间是**密钥块**（蓝色，循环滚动），右边是**明文块**（绿色）。每一步高亮当前处理的密文和密钥，密文块“往后跳`k_i`步”变成明文块（比如密文是`F`，密钥是`B`，就从`F`往回跳2步到`D`），同时播放“叮”的音效。自动播放时像“字母版贪吃蛇”，一步步完成解密~


---

## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰性、代码可读性、技巧实用性**三个维度筛选了3份优质题解，它们各有亮点，适合不同阶段的学习者参考~
</eval_intro>

**题解一：作者ingu（赞487）**
* **点评**：这份题解的代码**短到“极致”**，却藏着一个超实用的ASCII技巧——`x & 31`。因为大写字母（A=65）和小写字母（a=97）的二进制后5位完全相同（比如A是01000001，a是01100001，后5位都是00001），`&31`（二进制11111）刚好能取出这个“字母顺序”（A/a→1，B/b→2，…，Z/z→26）。代码里`(k[i%k.length()]&31)-1`算出密钥的偏移步数，`c[i]-t`直接调整密文字符，边界用`+26`处理。整个逻辑“一刀见血”，适合想学习**高效字符处理技巧**的同学。

**题解二：作者qhr2023（赞4）**
* **点评**：这份题解用**函数封装**的方式处理大小写，逻辑特别清晰。函数`m(char k, char c)`接收密钥和密文字符，分四种情况（大密钥+大密文、大密钥+小密文、小密钥+大密文、小密钥+小密文）计算明文。比如`(c-k+26)%26+'a'`直接算出小写明文，`(c-'A'-k+'a'+26)%26+'A'`处理大密文+小密钥的情况。代码结构规整，适合想学习**模块化编程**的同学。

**题解三：作者3_14（赞0）**
* **点评**：这份题解把“字符转数字”“数字转字符”“解密逻辑”分别封装成函数，**可读性拉满**。比如`charToNum`函数统一将字母转成0-25的数字，`numToChar`根据大小写将数字转回字符，`vigenereDecrypt`函数处理整个解密流程。这种写法像“搭积木”，每一步都很明确，适合刚学字符串处理的同学模仿。


---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解密Vigenère密码时，大家最容易卡壳的三个点，我帮你总结好了应对策略~
</difficulty_intro>

1.  **关键点1：如何保持明文的大小写与密文一致？**
    * **分析**：密文是大写，明文必须是大写；密文是小写，明文必须是小写。解决方案是**先记录密文的大小写**（比如用`isupper(c)`判断），将密文转成数字处理后，再根据记录的大小写转回字符。比如题解三中的`isUpper`变量，就是用来记住密文的大小写的。
    * 💡 **学习笔记**：大小写处理的核心是“先拆后合”——拆成数字计算，合的时候还原大小写。

2.  **关键点2：如何循环使用密钥？**
    * **分析**：当密文长度超过密钥时，密钥要重复用（比如密钥是`abc`，密文第4位用`a`，第5位用`b`）。解决方案是用`i % 密钥长度`——`i`是密文的当前位置，`%`运算会让密钥的索引循环（0→1→2→0→1→…）。比如题解一中的`k[i%k.length()]`，就是循环取密钥的字符。
    * 💡 **学习笔记**：循环问题优先想到`%`运算，它是“循环工具人”！

3.  **关键点3：如何避免偏移时“跑过界”？**
    * **分析**：比如密文是`A`（数字0），密钥是`B`（数字1），`0-1=-1`，这时候要绕到字母表末尾（Z，数字25）。解决方案是`(x + 26) % 26`——加26确保结果非负，再取模26回到0-25的范围。比如题解二中的`(c-k+26)%26`，就是处理负数的关键。
    * 💡 **学习笔记**：环形问题（比如星期、字母表）的边界处理，都可以用“加周期再取模”解决！

### ✨ 解题技巧总结
- **技巧1：ASCII码简化字符计算**：用`c - 'A'`（大写）或`c - 'a'`（小写）将字母转成数字，避免复杂的查表。
- **技巧2：函数封装提升可读性**：把重复的逻辑（比如字符转数字）写成函数，代码更简洁，调试更方便。
- **技巧3：提前处理边界**：在计算时就用`(x + 26) % 26`处理负数，避免后续判断。


---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心代码**，它综合了所有优质题解的思路，清晰又完整~
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码整合了“字符转数字”“循环密钥”“大小写处理”三大核心逻辑，适合作为基础模板。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    // 将字符转为0-25的数字（忽略大小写）
    int charToNum(char c) {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        else return c - 'a';
    }

    // 将数字转为字符（根据原密文的大小写）
    char numToChar(int num, bool isUpper) {
        return isUpper ? ('A' + num) : ('a' + num);
    }

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        int keyLen = key.size();
        int cipherLen = cipher.size();

        for (int i = 0; i < cipherLen; ++i) {
            char c = cipher[i];
            bool isUpper = (c >= 'A' && c <= 'Z');
            int cNum = charToNum(c);
            int kNum = charToNum(key[i % keyLen]); // 循环取密钥
            int mNum = (cNum - kNum + 26) % 26; // 解密公式
            cout << numToChar(mNum, isUpper);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码分三步：① 读取密钥和密文；② 遍历密文的每个字符，转成数字；③ 用循环密钥计算明文数字，转回字符并输出。核心是`charToNum`和`numToChar`函数处理大小写，`i%keyLen`循环密钥，`(cNum - kNum +26)%26`处理边界。

---
<code_intro_selected>
接下来看三份优质题解的**核心片段**，感受不同的技巧~
</code_intro_selected>

**题解一：作者ingu**
* **亮点**：用`&31`技巧快速获取字母顺序，代码超简洁。
* **核心代码片段**：
    ```cpp
    for (int i=0;i<c.length();i++) {
        int t=(k[i%k.length()]&31)-1;
        c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
    }
    ```
* **代码解读**：
    > ① `k[i%k.length()]&31`：取出密钥字符的后5位，得到1-26的顺序（比如A/a→1，B/b→2）；② `t`是偏移步数（减1是因为1→0步，2→1步）；③ `c[i]&31`取出密文的字母顺序，减`t`后如果是正数，直接调整字符；否则加26（比如密文是A，t=1，`1-1=0`→A-1=`@`，加26变成`Z`）。
* 💡 **学习笔记**：`&31`是处理字母大小写的“神技巧”，但要记得`&`是二进制运算哦~

**题解二：作者qhr2023**
* **亮点**：用函数处理所有大小写情况，逻辑清晰。
* **核心代码片段**：
    ```cpp
    char m (char k, char c) {
        if (k>='a'&&c>='a')
            return (c-k+26)%26+'a';
        else if (k>='a'&&c<='Z')
            return (c-'A'-k+'a'+26)%26+'A';
        else if (k<='Z'&&c>='a')
            return (c-'a'-k+'A'+26)%26+'a';
        else
            return (c-k+26)%26+'A';
    }
    ```
* **代码解读**：
    > 函数分四种情况：① 小密钥+小密文：直接`c-k`加26取模，加`a`；② 小密钥+大密文：先把密文转成0-25（`c-'A'`），密钥转成0-25（`k-'a'`），计算后加`A`；③ 大密钥+小密文：类似②；④ 大密钥+大密文：直接`c-k`加26取模，加`A`。覆盖了所有大小写组合！
* 💡 **学习笔记**：复杂的条件判断可以用函数封装，避免重复代码~

**题解三：作者3_14**
* **亮点**：完整的函数封装，模块化编程的典范。
* **核心代码片段**：
    ```cpp
    string vigenereDecrypt(const string& ciphertext, const string& key) {
        string plaintext;
        int keyLength = key.length();
        for (int i = 0; i < ciphertext.size(); ++i) {
            char c = ciphertext[i];
            bool isUpper = (c >= 'A' && c <= 'Z');
            int cNum = charToNum(c);
            int kNum = charToNum(key[i % keyLength]);
            int mNum = (cNum - kNum + 26) % 26;
            plaintext.push_back(numToChar(mNum, isUpper));
        }
        return plaintext;
    }
    ```
* **代码解读**：
    > 函数`vigenereDecrypt`接收密文和密钥，返回明文。遍历密文时，先记录大小写，转成数字计算，再转回字符存入`plaintext`。这种写法把“解密”这个复杂操作包装成一个函数，主函数只需要调用它——就像“黑盒工具”，用起来超方便！
* 💡 **学习笔记**：模块化编程能让代码更易读、易维护，大型项目中必备~


---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“看”到解密的过程，我设计了一个**8位像素风的动画**——像玩FC游戏一样，一步步破解密码！
</visualization_intro>

### ✨ 动画设计总览
- **主题**：像素字母的“逆向奔跑”——密文字母（红色）沿着字母表跑道往回跑，密钥（蓝色）是“步数提示牌”，跑完变成明文字母（绿色）。
- **风格**：FC红白机风格，用16色像素块（红、蓝、绿、黑、白），字体是经典的8位点阵字。
- **音效**：① 每处理一个字符：播放“叮”的像素音；② 解密完成：播放“咚咚”的胜利音；③ 错误（比如输入非字母）：播放“哔”的提示音。
- **交互控制**：① 单步执行：点击“下一步”，看一个字符的解密过程；② 自动播放：滑动“速度条”调整快慢，动画自动运行；③ 重置：回到初始状态，重新开始。

### 🎬 动画关键帧演示
1. **初始化界面**：
   - 屏幕分三部分：左边是**密文区**（红色像素块，显示输入的密文字符），中间是**密钥区**（蓝色像素块，循环滚动显示密钥），右边是**明文区**（灰色像素块，待填充）。
   - 底部控制面板：“开始”“单步”“重置”按钮，速度滑块（从“慢”到“快”）。

2. **第一步：处理第一个字符**：
   - 密文区第一个字符（比如`F`）闪烁，密钥区第一个字符（比如`B`）闪烁（蓝色变亮）。
   - 弹出文字气泡：“现在处理密文`F`，密钥是`B`（偏移2步）~”
   - 密文块`F`开始“往后跳”：从`F`→`E`→`D`，每跳一步播放“叮”的声音。
   - 明文区第一个位置变成`D`（绿色），文字气泡：“密文`F`往回跳2步，得到明文`D`！”

3. **第二步：循环密钥**：
   - 密文区第二个字符（比如`G`）闪烁，密钥区第二个字符（比如`C`）闪烁。
   - 文字气泡：“密钥用完了？没关系，循环用！现在密钥是`C`（偏移3步）~”
   - 密文块`G`往回跳3步→`D`，明文区第二个位置变成`D`。

4. **完成动画**：
   - 所有密文字符处理完毕，明文区全变成绿色，播放“咚咚”的胜利音。
   - 弹出提示：“解密完成！明文是：……”

### 🛠️ 技术实现小细节
- **字母表映射**：用数组`alphabet[] = {'A','B',...,'Z'}`，数字0对应`A`，25对应`Z`。
- **像素块绘制**：用Canvas的`fillRect(x, y, 16, 16)`画每个字符块（16x16像素），红色`#FF0000`，蓝色`#0000FF`，绿色`#00FF00`。
- **音效实现**：用Web Audio API生成正弦波音效，“叮”是440Hz（A调），“咚咚”是330Hz+523Hz（E调+C调），“哔”是100Hz（低频）。

<visualization_conclusion>
这个动画把抽象的“字符偏移”变成了直观的“像素块奔跑”，你能清楚看到每一步的变化——再也不用死记公式啦！


---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“**字符串的循环偏移**”，这种思路能解决很多类似问题~
</similar_problems_intro>

### 🔍 通用思路迁移
- **场景1**：凯撒密码（单表密码，密钥是固定步数）——比如`ROT13`加密，就是偏移13步，解密同理。
- **场景2**：字符串的循环移位——比如将字符串`abcde`循环左移2位变成`cdeab`，可以用`%`运算处理。
- **场景3**：密码学中的多表密码——比如Playfair密码，也是通过查表和循环处理字符。

### 📚 洛谷练习推荐
1.  **洛谷 P1078** - [NOIP2012 普及组] 引水入城
   * 🗣️ **推荐理由**：虽然是搜索题，但需要处理字符串的循环输入，能巩固`%`运算的用法。
2.  **洛谷 P3375** - KMP字符串匹配
   * 🗣️ **推荐理由**：经典的字符串处理题，需要理解字符串的前缀和后缀，提升对字符串的敏感度。
3.  **洛谷 P1598** - 垂直柱状图
   * 🗣️ **推荐理由**：需要统计字符出现次数并输出图形，能练习字符到数字的转换。
4.  **洛谷 P2249** - 【深基13.例1】查找
   * 🗣️ **推荐理由**：虽然是二分查找题，但输入是字符串，需要处理字符的比较，巩固字符串处理技巧。


---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我挖到了几个**超实用的“踩坑经验”**，帮你少走弯路~
</insights_intro>

> **经验1（来自ingu）**：“字母的ASCII码后5位是一样的，用`&31`能快速取顺序！”  
> **点评**：这个技巧太香了！比如`'A'&31=1`，`'a'&31=1`，直接忽略大小写——再也不用写`if`判断大写小写了！

> **经验2（来自qhr2023）**：“处理大小写要分情况，别漏了组合！”  
> **点评**：很多同学会忘“大密文+小密钥”或“小密文+大密钥”的情况，用函数分四种情况处理，能覆盖所有可能性~

> **经验3（来自3_14）**：“封装函数能让代码更干净！”  
> **点评**：把重复的逻辑写成函数，比如`charToNum`，不仅减少代码量，还能避免“复制粘贴”带来的错误~


---

<conclusion>
Vigenère密码的解密过程，本质是“**将字符转成数字，用数学运算处理，再转回字符**”。掌握了这个思路，你能解决很多字符串处理题！记住：**复杂的问题，拆成小步骤就简单了**——比如把“解密”拆成“字符转数字→循环密钥→计算明文→转回字符”。  

下次遇到字符串题，不妨试试今天学的技巧：用`%`循环，用`(x+26)%26`处理边界，用函数封装逻辑。你一定能破解更多“密码”！💪
</conclusion>

---

---
处理用时：169.87秒