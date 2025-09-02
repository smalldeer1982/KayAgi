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
# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡

<introduction>
今天我们来一起分析“Vigenère密码”这道C++编程题。这道题主要考察字符处理、循环密钥应用和模运算的综合运用。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用` (侧重基础字符处理、模运算及循环逻辑)

🗣️ **初步分析**：
> 解决“Vigenère密码”问题的关键在于理解加密与解密的逆过程。Vigenère加密的本质是**循环移位**：每个明文字符根据对应密钥字符的字母顺序（如A=0，B=1...Z=25），向后循环移位（例如密钥是B时，明文A→B，Z→A）。解密时，则需要向前循环移位相同位数。  
> 例如，密文是F（对应5），密钥是B（对应1），则明文是5-1=4（对应E）；若密文是A（对应0），密钥是B（对应1），则明文是(0-1+26)%26=25（对应Z）。  
> 本题的核心难点是：1）保持明文与密文的大小写一致；2）密钥循环使用（密文长度可能超过密钥）；3）处理负数移位（通过加26再取模避免）。  
> 优质题解的思路高度统一：将密钥和密文字符转换为0-25的数值（忽略大小写），计算明文数值为`(密文数值 - 密钥数值 + 26) % 26`，再转换回原大小写字符。  
> 可视化设计上，我们可以用**8位像素轮盘**演示：每个字符对应一个轮盘（A-Z循环排列），密钥字符指示移位位数，密文字符轮盘逆时针转动对应位数，最终停在明文字符的位置，配合“咔嗒”音效提示移位。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：作者：ingu (赞：472)**
* **点评**：这份题解堪称“极简典范”。作者利用位运算（`&31`）巧妙将字符转换为0-25的数值（因'A'-'Z'和'a'-'z'的ASCII码后5位相同），代码仅10行却覆盖所有核心逻辑。变量命名简洁（`t`表示密钥偏移量），循环处理密钥的模运算（`i%k.length()`）非常巧妙。从实践角度看，代码可直接用于竞赛，边界处理（如负数移位）通过条件判断完美解决，是学习字符处理技巧的绝佳示例。

**题解二：作者：Sinwind (赞：3)**
* **点评**：此题解结构清晰，通过封装`decryption`函数分离核心逻辑与输入输出，符合模块化编程思想。函数中统一将字符转换为大写处理（`toupper`），避免了大小写混淆；返回时根据原密文的大小写选择'A'或'a'基准，逻辑直白易懂。代码注释明确，变量名（`temp_c`、`temp_k`）含义清晰，适合新手学习如何将问题拆解为子函数。

**题解三：作者：ShirasuAzusaSaikou (赞：1)**
* **点评**：此题解的亮点在于“统一密钥大小写”的处理——将密钥全部转为小写（`tolower(i)`），简化后续计算。代码利用范围遍历（`for(auto &i : k)`）和三元运算符（`(m[i] >= 'a')? 'a': 'A'`），在保持简洁的同时兼顾可读性。循环密钥的处理（`ki = (ki + 1) % kl`）逻辑清晰，是“循环模式”问题的典型实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决Vigenère密码问题时，以下三个关键点需要特别注意：
</difficulty_intro>

1.  **关键点1：字符的大小写保持**  
    * **分析**：密文的大小写需与明文一致（如密文是小写，明文也需是小写）。优质题解通常通过两种方式处理：一种是记录密文的大小写状态（如Sinwind的`isupper(c)`判断），另一种是统一转换为大写/小写计算后再恢复（如ShirasuAzusaSaikou的`tolower`）。  
    * 💡 **学习笔记**：处理大小写时，“先记录状态，再恢复”比“直接转换”更不易出错。

2.  **关键点2：密钥的循环使用**  
    * **分析**：当密文长度大于密钥时，需循环使用密钥（如密文第i位对应密钥第`i%密钥长度`位）。所有优质题解均通过模运算（`i%k.length()`）轻松解决此问题，这是循环模式问题的通用技巧。  
    * 💡 **学习笔记**：模运算（`%`）是处理“循环重复”场景的核心工具。

3.  **关键点3：循环移位的负数处理**  
    * **分析**：当密文数值小于密钥数值时（如密文是A=0，密钥是B=1），直接相减会得到负数（0-1=-1）。此时需加26再取模（`(-1+26)%26=25`），确保结果在0-25范围内。优质题解通过`(c - k + 26) % 26`统一处理这种情况，避免条件判断。  
    * 💡 **学习笔记**：`(x + n) % n`是解决循环负数问题的万能公式（n为循环周期，此处n=26）。

### ✨ 解题技巧总结
<summary_best_practices>
- **统一基准值**：将字符统一转换为大写或小写（如`toupper`），简化数值计算。  
- **模运算循环**：用`i % len`处理密钥的循环使用，避免数组越界。  
- **公式统一**：用`(c - k + 26) % 26`替代条件判断，同时处理正负移位，代码更简洁。  
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，兼顾简洁性与可读性：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了ingu的极简风格与Sinwind的模块化思想，通过统一转换字符为数值、模运算处理循环密钥，最终恢复原大小写。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    #include <cctype>
    using namespace std;

    char decrypt(char cipher_char, char key_char) {
        // 统一转换为大写计算数值（0-25）
        int c = toupper(cipher_char) - 'A';
        int k = toupper(key_char) - 'A';
        int m = (c - k + 26) % 26; // 计算明文数值（避免负数）
        // 恢复原大小写
        return isupper(cipher_char) ? (m + 'A') : (m + 'a');
    }

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        int key_len = key.size();
        for (int i = 0; i < cipher.size(); ++i) {
            char key_char = key[i % key_len]; // 循环使用密钥
            cout << decrypt(cipher[i], key_char);
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码分为两部分：`decrypt`函数负责单个字符的解密（统一转大写计算数值，恢复原大小写）；`main`函数处理输入，循环使用密钥（`i % key_len`），调用`decrypt`输出明文。核心逻辑清晰，变量命名直观，适合直接用于竞赛。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：作者：ingu**
* **亮点**：利用位运算`&31`快速提取字符的“字母顺序值”（A-Z和a-z的ASCII码后5位相同），代码极简。
* **核心代码片段**：
    ```cpp
    for (int i=0;i<c.length();i++) {
        int t=(k[i%k.length()]&31)-1; // 密钥字符的字母顺序（A=1→0，B=2→1...）
        c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26; // 计算明文（保持原大小写）
    }
    ```
* **代码解读**：  
  `k[i%k.length()]&31`将密钥字符（无论大小写）转换为1-26的数值（如'A'=65→65&31=1，'a'=97→97&31=1），减1后得到0-25的偏移量`t`。`c[i]&31`同理提取密文字符的数值，若`(c数值 - t) >0`则直接减，否则加26（如c数值=0，t=1→0-1+26=25）。最后结果直接修改原密文字符（保持原大小写）。  
* 💡 **学习笔记**：位运算`&31`是快速提取字母顺序的“神来之笔”，适用于所有ASCII字符（A-Z和a-z的后5位相同）。

**题解二：作者：Sinwind**
* **亮点**：通过函数封装分离核心逻辑，代码结构清晰，适合模块化编程学习。
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
  `toupper`统一转换字符为大写，避免大小写干扰。`m`的基准值根据原密文的大小写选择（'A'或'a'）。条件判断`temp_c >= temp_k`处理正负移位：若密文数值≥密钥数值，直接相减；否则加26再减（如temp_c=0，temp_k=1→0+26-1=25）。最后返回恢复大小写的明文字符。  
* 💡 **学习笔记**：函数封装能让主逻辑更清晰，适合复杂问题的拆解。

**题解三：作者：ShirasuAzusaSaikou**
* **亮点**：统一密钥为小写，简化计算；利用范围遍历处理密钥，代码简洁。
* **核心代码片段**：
    ```cpp
    for(auto &i : k) i = tolower(i); // 密钥统一转小写
    for(int i = 0; i < ml; i++){
        cout << (char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
        ki = (ki + 1) % kl; // 循环密钥索引
    }
    ```
* **代码解读**：  
  首先将密钥全部转为小写（`tolower(i)`），后续计算只需用小写基准（'a'）。`tolower(m[i]) - k[ki]`计算密文与密钥的数值差（均为小写），加26取模后得到明文字符的偏移量。最后根据原密文的大小写（`(m[i] >= 'a')? 'a': 'A'`）恢复基准值。  
* 💡 **学习笔记**：统一输入数据的格式（如全转小写）能减少后续条件判断，降低出错概率。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解Vigenère解密的过程，我们设计了一个**8位像素风格的“字母轮盘”动画**，让你“看”到每个字符的解密步骤！
</visualization_intro>

  * **动画演示主题**：`像素轮盘大冒险——Vigenère解密之旅`

  * **核心演示内容**：  
    屏幕左侧显示密文字符轮盘（A-Z循环排列，像素方块风格），右侧显示密钥字符轮盘。每一步选择一个密文字符和对应的密钥字符，轮盘逆时针转动（密钥字符的字母顺序位数），最终停在明文字符的位置。

  * **设计思路简述**：  
    8位像素风格（如FC游戏《超级玛丽》的界面）能降低学习压力；轮盘转动的动画直观展示“循环移位”的过程；音效（如“咔嗒”声）强化每一步的操作记忆；自动播放模式可让学习者观察完整解密流程。

  * **动画帧步骤与交互关键点**：

    1.  **初始化界面**：  
        - 顶部显示“Vigenère解密器”标题（像素字体），中间是两个轮盘（密文轮盘、密钥轮盘），底部是控制面板（开始/暂停、单步、重置按钮，速度滑块）。  
        - 背景音乐：8位风格的轻快旋律（类似《俄罗斯方块》BGM）。

    2.  **数据加载**：  
        - 输入密钥和密文字符串，轮盘初始显示所有字母（A-Z，像素方块颜色为淡蓝色）。  
        - 密钥轮盘用黄色框标注当前使用的密钥字符（如第0位是'A'，则'A'方块闪烁）。

    3.  **单步解密演示**：  
        - 点击“单步”按钮，当前密文字符（红色方块）和对应密钥字符（黄色方块）高亮。  
        - 密钥轮盘显示该字符的字母顺序（如密钥是'B'，显示“偏移量1”）。  
        - 密文轮盘逆时针转动1格（对应偏移量），停在明文字符的位置（绿色方块），伴随“咔嗒”音效。  
        - 同步高亮代码中的关键行（如`(c - k + 26) % 26`），并显示文字提示：“密文F（5）- 密钥B（1）= 4 → 明文E”。

    4.  **自动播放模式**：  
        - 点击“自动播放”，轮盘按设定速度（滑块调节）自动转动，依次处理每个字符。  
        - 每完成一个字符解密，明文字符在底部输出区逐渐拼接成完整字符串（类似打字机效果）。

    5.  **结束状态**：  
        - 所有字符解密完成后，输出区显示完整明文，轮盘停止转动，播放“胜利”音效（上扬的“叮”声），并显示“解密成功！”的像素烟花动画。

  * **旁白提示**：  
    - （单步前）“现在处理第i个字符，密文是`C`，密钥是`K`，我们需要将`C`逆时针转`K的字母顺序`位，得到明文。”  
    - （转动时）“看！密文轮盘转了`K的字母顺序`位，停在了`M`，这就是明文！”

<visualization_conclusion>
通过这个像素轮盘动画，你不仅能看到每个字符的解密过程，还能直观理解“循环移位”和“模运算”的作用。下次遇到类似问题时，你也能像轮盘一样“转”出答案啦！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环模式”和“字符移位”，这类技巧还能解决以下问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 循环模式处理：如游戏中的“技能冷却循环”（用`i%冷却时间`判断是否可用）。  
    - 字符移位：如凯撒密码（固定移位）、替换密码（字符映射表）。  
    - 模运算应用：如日期计算（`(当前天数 + 偏移) % 7`求星期几）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1328 生活大爆炸版石头剪刀布**  
        * 🗣️ **推荐理由**：需要处理循环模式（双方的出拳序列循环使用），与Vigenère的密钥循环类似，适合练习模运算的应用。  
    2.  **洛谷 P1553 数字反转（升级版）**  
        * 🗣️ **推荐理由**：涉及数字、分数、小数的反转，需要处理多种字符类型（数字、符号），锻炼字符处理能力。  
    3.  **洛谷 P1055 ISBN号码**  
        * 🗣️ **推荐理由**：通过模运算校验ISBN号的正确性，与Vigenère的`(x + n) % n`思路类似，适合巩固模运算技巧。

-----

## 7\. 学习心得与经验分享 

<insights_intro>
部分题解作者分享了调试时的经验，这些“踩坑”经历对我们很有启发：
</insights_intro>

> **参考经验 (来自 某题解作者)**：“一开始没注意密文的大小写要保持，直接转成大写计算后忘记恢复，导致输出全是大写。后来通过打印中间变量（如`cout << c[i]`）发现了问题。”

**点评**：这位作者的经验提醒我们，字符的大小写处理是常见易错点。调试时，打印关键变量（如转换后的数值、恢复的大小写）能快速定位问题。学习时，可以手动模拟小例子（如样例输入），验证每一步的计算是否正确。

-----

<conclusion>
本次关于“Vigenère密码”的C++解题分析就到这里。希望这份指南能帮助你掌握字符处理、模运算和循环模式的核心技巧。记住，编程的关键是“理解逻辑，多练多调”。下次遇到类似问题时，你一定能轻松解决！💪
</conclusion>

---
处理用时：211.21秒