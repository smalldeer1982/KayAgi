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



---
# 💡 Kay的C++算法解析：[NOIP 2012 提高组] Vigenère 密码 深入学习指南 💡

<introduction>
今天我们来一起分析“Vigenère 密码”这道题。Vigenère 密码是经典的多表加密算法，解密的关键在于理解字符间的偏移规律。本指南将帮助你梳理题目核心、掌握解密思路，并通过代码和可视化演示直观理解每一步操作！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（字符串处理、模运算、字符转换）

🗣️ **初步分析**：
Vigenère 密码的解密本质是“逆向偏移”。想象每个明文字符是密文字符“回退”密钥字符对应的步数（类似凯撒密码的反向操作）。例如，密钥是 'a'（偏移0），则密文=明文；密钥是 'b'（偏移1），则明文=密文回退1步（若密文是 'B'，明文是 'A'；若密文是 'A'，明文是 'Z'）。

核心难点在于：
1. 密钥循环使用：当密文比密钥长时，密钥需重复（用`i%k.length()`处理索引）。
2. 大小写保持：明文的大小写与密文一致，需单独记录。
3. 模运算处理：回退步数可能越界（如密文是 'A'，密钥是 'B'，需回退到 'Z'），需用`(c - k + 26) % 26`避免负数。

可视化设计思路：用8位像素风格展示“字符偏移工厂”，每个密文字符是一个小方块，密钥字符是“齿轮”。动画中，齿轮（密钥）推动密文方块回退对应步数，高亮当前处理的位置（如用黄色边框），并显示每一步的数值变化（如密文'A'=0，密钥'B'=1，明文=0-1+26=25→'Z'）。关键步骤（如越界回退）伴随“叮”的音效，完成解密时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过对比各题解的思路清晰度、代码规范性和算法有效性，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：作者：ingu (赞：472)**
* **点评**：此题解代码极短但逻辑精准。通过位运算`x & 31`统一处理大小写（因'A'和'a'的后5位相同），直接计算偏移量，避免复杂条件判断。代码变量命名简洁（如`t`表示密钥偏移量），边界处理（`c[i]-t>0`）巧妙，实践价值高（竞赛中可快速编写）。

**题解二：作者：Sinwind (赞：3)**
* **点评**：此题解将解密逻辑封装为`decryption`函数，结构清晰。通过`toupper`统一处理字符大小写，避免重复代码；返回时根据原字符大小写决定输出格式，严谨性强。适合学习函数封装和模块化编程。

**题解三：作者：ShirasuAzusaSaikou (赞：1)**
* **点评**：此题解代码简洁且高效。使用`tolower`统一密钥和密文的大小写，通过`(tolower(m[i]) - k[ki] + 26) % 26`直接计算偏移，最后根据原密文的大小写调整输出。逻辑流畅，适合理解“统一处理+还原”的思路。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解密Vigenère密码的关键在于解决以下三个核心问题，掌握这些能让你举一反三：
</difficulty_intro>

1.  **关键点1：密钥的循环使用**
    * **分析**：当密文长度超过密钥时，密钥需重复使用。例如，密钥是"abc"，密文第4位对应密钥第1位（索引`3%3=0`）。优质题解普遍用`i % k.length()`处理索引，简洁高效。
    * 💡 **学习笔记**：循环索引问题，模运算`i % len`是通用解法。

2.  **关键点2：大小写的保持**
    * **分析**：明文的大小写必须与密文一致。例如，密文是大写，明文也需大写。题解中常用两种方法：记录原字符的大小写（如Sinwind的`isupper(c)`），或统一转换后再还原（如Shirasu的`(m[i] >= 'a') ? 'a' : 'A'`）。
    * 💡 **学习笔记**：处理大小写时，先统一转换（如全转小写）计算偏移，再根据原格式还原，可简化逻辑。

3.  **关键点3：模运算处理越界**
    * **分析**：回退步数可能为负数（如密文'A'回退1步到'Z'）。公式`(c - k + 26) % 26`是关键，加26确保结果非负，模26保证在0-25范围内。
    * 💡 **学习笔记**：涉及循环的数值操作（如字母表），模运算能有效处理边界。

### ✨ 解题技巧总结
- **统一转换**：将密钥和密文统一为大写或小写计算偏移，再还原原格式，减少条件判断。
- **模运算优先**：循环索引和越界处理用`%`，简洁且不易出错。
- **函数封装**：将核心解密逻辑封装为函数（如`decryption(c, k)`），提高代码可读性和复用性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，给出一个简洁且完整的核心实现，兼顾可读性和效率。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了ingu和Sinwind的思路，统一处理大小写，用模运算解决循环和越界问题，代码简洁高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    #include <cctype>
    using namespace std;

    char decrypt(char cipher_char, char key_char) {
        // 统一转换为大写计算偏移量（a/A的偏移量相同）
        int c = tolower(cipher_char) - 'a'; // 密文字符的0-25值
        int k = tolower(key_char) - 'a';    // 密钥字符的0-25值
        int plain = (c - k + 26) % 26;      // 计算明文的0-25值
        // 还原原大小写
        return isupper(cipher_char) ? plain + 'A' : plain + 'a';
    }

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        for (int i = 0; i < cipher.size(); ++i) {
            // 密钥循环使用：i % key.size()
            cout << decrypt(cipher[i], key[i % key.size()]);
        }
        return 0;
    }
    ```
* **代码解读概要**：
  代码分为`decrypt`函数和主函数。`decrypt`函数负责单个字符的解密：先统一转小写计算偏移量（0-25），用`(c - k + 26) % 26`避免负数，最后根据原密文的大小写还原。主函数处理输入，循环调用`decrypt`，并通过`i % key.size()`实现密钥的循环使用。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：作者：ingu**
* **亮点**：用位运算`x & 31`统一处理大小写（因'A'-'Z'和'a'-'z'的ASCII码后5位相同），代码极短。
* **核心代码片段**：
    ```cpp
    int t=(k[i%k.length()]&31)-1;
    c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
    ```
* **代码解读**：
  - `k[i%k.length()]&31`：将密钥字符转为0-25（如'A'→1，'a'→1，因'A'=65→65&31=1，'a'=97→97&31=1）。
  - `t`是密钥的偏移量（题目中密钥字符对应偏移量为字符顺序-1，如'A'偏移0，'B'偏移1）。
  - `c[i]&31`将密文字符转为0-25，判断是否大于`t`：若大于，直接减`t`；否则加26再减`t`（避免负数）。
* 💡 **学习笔记**：位运算`&31`可快速提取字符的“字母顺序”，简化大小写处理。

**题解二：作者：Sinwind**
* **亮点**：函数封装清晰，逻辑分层，易读易维护。
* **核心代码片段**：
    ```cpp
    char decryption(char c, char k) {
        char temp_c = toupper(c);
        char temp_k = toupper(k);
        char m = (isupper(c)) ? 'A' : 'a';
        m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
        return m;
    }
    ```
* **代码解读**：
  - `toupper(c)`和`toupper(k)`统一转为大写，避免大小写干扰。
  - `m`的初始值设为'A'或'a'（根据密文的大小写），直接加上偏移量（`temp_c - temp_k`或`temp_c + 26 - temp_k`）。
* 💡 **学习笔记**：函数封装能让主逻辑更简洁，适合复杂问题的模块化处理。

**题解三：作者：ShirasuAzusaSaikou**
* **亮点**：代码简洁，用`tolower`统一处理，减少条件判断。
* **核心代码片段**：
    ```cpp
    cout << (char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
    ```
* **代码解读**：
  - `tolower(m[i]) - k[ki]`：统一转小写后计算偏移（k已提前转小写）。
  - `+26`和`%26`确保偏移量非负且在0-25之间。
  - `(m[i] >= 'a')? 'a': 'A'`：根据原密文的大小写决定基准字符（'a'或'A'）。
* 💡 **学习笔记**：统一转换后计算，再还原原格式，是处理大小写问题的通用技巧。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解解密过程，我们设计一个“像素字母工厂”动画，用8位风格展示密钥循环和字符回退的每一步！
</visualization_intro>

  * **动画演示主题**：`像素字母解密工厂`
  * **核心演示内容**：密文字符逐个进入“解密机器”，对应的密钥字符（循环显示）作为“齿轮”推动密文回退，最终输出明文字符。
  * **设计思路简述**：8位像素风格（类似FC游戏）降低学习门槛；齿轮动画（密钥循环）和字符回退（偏移计算）直观展示核心逻辑；音效（如齿轮转动声、字符落地声）强化操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 背景：像素风格的“解密工厂”，左侧是密文队列（黄色方块，标有字符），右侧是密钥齿轮（蓝色齿轮，标有字符）。
        - 控制面板：单步/自动播放按钮、速度滑块（1-5倍速）、重置按钮。

    2.  **密钥循环演示**：
        - 密钥齿轮初始显示密钥的第1个字符（如k="abc"，齿轮显示'A'）。
        - 处理第i个密文时，齿轮显示`k[i%3]`，用“旋转动画”（齿轮转一圈）提示密钥循环。

    3.  **字符解密过程**：
        - 密文字符（如'Y'）进入解密机器，齿轮（如'v'）开始转动。
        - 显示计算过程：`Y(24) - v(21) = 3 → 3 + 'A' = D？不，原密文是小写吗？`（根据原密文的大小写调整基准）。
        - 若密文是大写（如'Y'），则明文基准是'A'，计算`24 - 21 = 3 → 'D'`；若密文是小写（如'y'），基准是'a'，结果为'd'。
        - 字符回退时，用像素方块逐格移动（如从'Y'左移3格到'D'），越界时从'Z'跳到'A'（红色闪光提示）。

    4.  **音效与提示**：
        - 齿轮转动：“咔嗒”音效（每转一步）。
        - 字符移动：“滴答”音效（每移动一格）。
        - 完成解密：“叮”音效，明文字符放大显示。

    5.  **交互控制**：
        - 单步播放：点击“下一步”，手动控制每一步解密。
        - 自动播放：选择速度（如2倍速），自动演示完整解密过程。
        - 代码同步：右侧显示当前步骤对应的代码片段（如`(c - k + 26) % 26`），高亮执行行。

<visualization_conclusion>
通过这个动画，你可以直观看到密钥如何循环、字符如何回退，以及模运算如何处理越界。动手操作控制按钮，还能深入理解每一步的细节！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环偏移+模运算”，这类思路在字符串处理中很常见。以下是一些拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - 凯撒密码（单表偏移）：Vigenère是其多表扩展，思路类似但密钥循环。
    - 循环字符串处理（如字符串移位、循环同构）：用模运算处理索引循环。
    - 字符加密/解密（如ROT13）：固定偏移的模运算应用。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1118 [USACO06FEB] Backward Digit Sums G**  
        * 🗣️ **推荐理由**：涉及循环和模运算，锻炼对索引和数值循环的处理能力。
    2.  **洛谷 P1125 [NOIP2008 提高组] 笨小猴**  
        * 🗣️ **推荐理由**：字符频率统计+模运算判断质数，巩固字符处理技巧。
    3.  **洛谷 P1055 [NOIP2008 普及组] ISBN号码**  
        * 🗣️ **推荐理由**：字符串校验+模运算，练习字符遍历和条件判断。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自 123456Zhe)**：“一开始没考虑密文是'A'且密钥是'B'的情况，导致解密结果错误。后来通过打印中间变量（如密文的数值、密钥的数值），发现越界时需要加26再取模。”

**点评**：这位作者的经验很实用！在处理循环数值（如字母表）时，越界是常见错误。通过打印中间变量（如字符的0-25值）可以快速定位问题。这提醒我们，调试时不要怕“笨方法”，直接观察关键变量更有效。

-----

<conclusion>
Vigenère密码的解密核心是“循环偏移+模运算”，关键在于处理好密钥循环、大小写保持和越界回退。通过优质题解的学习和可视化动画的辅助，相信你已经掌握了其中的技巧。接下来，动手编写代码并尝试拓展练习，巩固所学吧！💪
</conclusion>

-----

---
处理用时：166.98秒