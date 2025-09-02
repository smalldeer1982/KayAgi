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
今天我们来一起分析“Vigenère密码”这道C++编程题。这道题是经典的密码学问题，核心在于理解如何通过密钥和密文逆向推导出明文。本指南将帮助大家梳理题目思路，掌握核心算法，并通过可视化演示和代码赏析加深理解。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（侧重字符串处理与模运算的基础运用）

🗣️ **初步分析**：
> Vigenère密码的解密问题，本质是对每个密文字符进行“逆向循环移位”操作。简单来说，加密时每个明文字符会被密钥字符“推”若干位（如密钥是`b`，明文`e`会被推成`f`），解密则是把这个过程反过来——把密文字符“拉”回原位（如密文`f`遇到密钥`b`，要拉回`e`）。如果拉过了头（比如密文是`a`，密钥是`b`），就需要从字母表末尾循环回来（`a`拉1位变成`z`）。

- **题解思路对比**：多数题解围绕“字符转数字→计算偏移→模26处理循环→转回原大小写”展开。例如，有的直接用公式`(c - k + 26) % 26`计算（简洁高效），有的用打表法模拟密码表（直观但代码稍长）。核心差异在于如何处理大小写和循环逻辑。
- **核心算法流程**：对每个密文字符，取对应位置的密钥字符（密钥循环使用），将两者转换为0-25的数字（忽略大小写），计算`(密文数字 - 密钥数字 + 26) % 26`得到明文数字，再根据原密文的大小写转换回字母。
- **可视化设计**：我们将设计一个8位像素风格的“密码机”动画，用像素块表示字符，密钥指针循环移动（类似FC游戏的指针动画），字符转换时用颜色渐变（如密文红→明文绿），模26时用“循环箭头”高亮，关键步骤（如负数处理）伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，我筛选出以下3篇优质题解：
</eval_intro>

**题解一：作者ingu（赞：478）**
* **点评**：这份题解非常简洁巧妙！作者利用ASCII码的位运算（`&31`）统一处理大小写（因为大写和小写字母的后5位相同），直接计算偏移量。代码仅10行，变量命名清晰（如`t`表示密钥的偏移量），边界条件（如`c[i]-t>0`）处理简洁，是竞赛中“短代码+高效”的典范。

**题解二：作者Sinwind（赞：3）**
* **点评**：此题解结构清晰，将解密逻辑封装为`decryption`函数，代码可读性强。作者先统一将字符转为大写计算偏移，再根据原密文的大小写还原，逻辑步骤明确。这种“先计算再还原”的思路，非常适合新手理解。

**题解三：作者qhr2023（赞：3）**
* **点评**：此题解直接应用公式`(c - k + 26) % 26`，代码简短且覆盖所有大小写情况。虽然条件判断较多，但每个分支逻辑直白（如`k>='a'&&c>='a'`），适合理解基础的字符转换规则。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键在于处理三个核心问题，我们逐一分析：
</difficulty_intro>

1.  **关键点1：如何统一处理大小写？**
    * **分析**：题目要求明文保持密文的大小写。例如，密文是`H`（大写），明文也必须是大写；密文是`e`（小写），明文也是小写。优质题解通常的做法是：先将密文和密钥统一转为小写（或大写）计算偏移量，再根据原密文的大小写还原。例如，`Sinwind`的题解中，用`isupper(c)`判断原密文的大小写，最后加上`'A'`或`'a'`。
    * 💡 **学习笔记**：大小写不影响偏移量计算，只需记录原大小写，最后还原即可。

2.  **关键点2：如何处理循环移位（模26）？**
    * **分析**：当密文字符的数字小于密钥字符的数字时（如密文是`a`，密钥是`b`），直接相减会得到负数（`0 - 1 = -1`），这时候需要加26再取模（`(-1 + 26) % 26 = 25`，对应`z`）。优质题解中，`ingu`用`c[i]-t>0?c[i]-t:c[i]-t+26`处理，`qhr2023`用`(c - k + 26) % 26`统一处理，两种方法都能解决循环问题。
    * 💡 **学习笔记**：模26运算能自动处理循环，公式`(x + 26) % 26`可确保结果非负。

3.  **关键点3：如何循环使用密钥？**
    * **分析**：当密文长度大于密钥长度时，需要重复使用密钥。例如，密文长度是10，密钥长度是3，则密钥的索引依次是0,1,2,0,1,2,0,1,2,0。优质题解中，`ingu`用`i%k.length()`直接取模，简洁高效。
    * 💡 **学习笔记**：取模运算`i % len`是循环使用数组的“万能钥匙”。

### ✨ 解题技巧总结
<summary_best_practices>
- **字符转数字**：用`c - 'A'`（大写）或`c - 'a'`（小写）将字符转为0-25的数字，忽略大小写时可用`(c & 31) - 1`（如`ingu`的位运算技巧）。
- **统一处理逻辑**：先计算偏移量（忽略大小写），再根据原字符的大小写还原，避免重复判断。
- **模运算防错**：涉及循环时，用`(x + 26) % 26`确保结果在0-25范围内，避免负数错误。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，选择`ingu`的简洁代码作为通用核心实现，并补充注释帮助理解。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合自`ingu`的题解，因其代码简洁、逻辑清晰，且覆盖所有边界条件，适合作为通用实现参考。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        for (int i = 0; i < cipher.length(); ++i) {
            // 计算密钥字符的偏移量（0-25）：key[i%len] & 31 得到'A'-'Z'或'a'-'z'的后5位（即1-26），减1得0-25
            int offset = (key[i % key.length()] & 31) - 1;
            // 计算明文：密文字符的后5位（1-26）减offset，若结果<=0则加26（模26）
            cipher[i] = ((cipher[i] & 31) - offset > 0) ? 
                        (cipher[i] - offset) : (cipher[i] - offset + 26);
        }
        cout << cipher << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取密钥和密文。对于每个密文字符，通过`i % key.length()`循环取密钥字符，用位运算`&31`统一处理大小写（得到1-26的数字），减1得到0-25的偏移量。然后计算明文：若密文数字减偏移量大于0，直接相减；否则加26（模26）。最后输出处理后的明文。

---
<code_intro_selected>
接下来，我们分析3篇优质题解的核心代码片段，学习其中的技巧。
</code_intro_selected>

**题解一：作者ingu**
* **亮点**：用位运算`&31`统一处理大小写，代码极简。
* **核心代码片段**：
    ```cpp
    int t=(k[i%k.length()]&31)-1;
    c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
    ```
* **代码解读**：
    > `k[i%k.length()]&31`：将密钥字符（无论大小写）的ASCII码与31（二进制`11111`）按位与，得到后5位（如`'A'`是65→65&31=1，`'a'`是97→97&31=1），即1-26的数字。减1后得到0-25的偏移量`t`。  
    > `(c[i]&31)-t>0`：同样处理密文字符，得到1-26的数字，减`t`判断是否大于0。若大于0，直接减`t`得到明文；否则加26（如`1-2= -1 → -1+26=25`，对应`z`）。
* 💡 **学习笔记**：位运算`&31`是快速统一大小写的技巧（因为大写和小写字母的后5位相同）。

**题解二：作者Sinwind**
* **亮点**：函数封装，逻辑清晰。
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
    > `toupper(c)`和`toupper(k)`：将密文和密钥统一转为大写，方便计算偏移量。  
    > `(isupper(c)) ? 'A' : 'a'`：记录原密文的大小写，确定明文的基准字符（`'A'`或`'a'`）。  
    > `temp_c >= temp_k`：判断密文数字是否大于等于密钥数字。若是，直接减；否则加26再减（如`'A'(0) - 'B'(1)` → `0 + 26 -1=25`，对应`z`）。
* 💡 **学习笔记**：函数封装能提高代码可读性，适合复杂逻辑的拆分。

**题解三：作者qhr2023**
* **亮点**：直接应用公式，覆盖所有大小写情况。
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
    > 四个条件分支分别处理“密钥小写+密文小写”“密钥小写+密文大写”等情况。例如，当`k`是小写（`k>='a'`）、`c`是大写（`c<='Z'`）时，`k`转为小写数字（`k-'a'`），`c`转为大写数字（`c-'A'`），计算`(c-'A' - (k-'a') + 26) % 26`，再转回大写（`+'A'`）。
* 💡 **学习笔记**：直接应用公式`(c - k + 26) % 26`时，需注意字符的大小写对应的基准（`'A'`或`'a'`）。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解解密过程，我们设计一个8位像素风格的“密码机”动画，让你“看”到每个字符如何从密文变明文！
</visualization_intro>

  * **动画演示主题**：`像素密码机大冒险`
  * **核心演示内容**：密文、密钥、明文的字符转换过程，重点展示密钥循环使用和循环移位（模26）的关键步骤。
  * **设计思路简述**：采用FC红白机风格的像素界面（8色调色板，如红、绿、黄），用“密码机”的齿轮动画表示字符转换，密钥指针循环移动（类似《超级马里奥》的金币滚动），模26时用“循环箭头”高亮，关键操作（如减偏移、加26）伴随“叮”的音效，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **初始化界面 (8位像素风)**：
        - 屏幕分为三行：顶部显示“密钥”（黄色像素块），中间显示“密文”（红色像素块），底部显示“明文”（绿色像素块，初始为空）。
        - 控制面板：单步/自动按钮、速度滑块（1x-5x）、重置按钮。

    2.  **密钥循环动画**：
        - 密钥字符右侧有一个白色箭头指针（类似FC菜单指针），每处理一个密文字符，指针右移；若到密钥末尾，指针跳回开头（伴随“滴答”音效）。

    3.  **字符转换过程**：
        - 选中当前密文字符（红色块闪烁）和对应密钥字符（黄色块闪烁）。
        - 密文字符块向右移动，与密钥字符块碰撞，弹出一个“计算气泡”（显示`c - k`的结果）。
        - 若结果≥0（如`f - b = 4`），明文块显示`e`（绿色）；若结果<0（如`a - b = -1`），气泡中出现“+26”动画，结果变为25，明文块显示`z`（绿色）。

    4.  **音效与反馈**：
        - 指针移动：“滴答”声。
        - 字符碰撞：“叮”声（类似《俄罗斯方块》的落块音）。
        - 模26处理：“嗡”的长音（强调循环）。
        - 全部转换完成：“胜利”音效（类似《超级玛丽》的通关音）。

    5.  **交互控制**：
        - 单步模式：点击“下一步”，逐字符演示转换。
        - 自动模式：选择速度后，密码机自动运行，指针快速移动，字符块连续转换。
        - 代码同步：右侧显示当前步骤对应的核心代码（如`c[i] = ...`），高亮执行行。

<visualization_conclusion>
通过这个像素动画，你可以清晰看到每个字符的转换过程，特别是密钥循环和模26的处理逻辑，就像在玩一个解密小游戏！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环偏移+模运算”，这种思路在很多字符串处理问题中都会用到。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 循环规则处理（如石头剪刀布的循环胜负）。
      - 周期性字符串操作（如凯撒密码、栅栏密码）。
      - 字符偏移的模运算（如日期循环、星期计算）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1328 生活大爆炸版石头剪刀布**
        * 🗣️ **推荐理由**：需要处理循环的胜负规则，与Vigenère的循环移位思路类似，适合练习模运算的应用。
    2.  **洛谷 P1553 数字反转（升级版）**
        * 🗣️ **推荐理由**：涉及数字和字符串的循环反转，需要处理前导零和循环字符，锻炼字符串处理能力。
    3.  **洛谷 P2678 跳石头**
        * 🗣️ **推荐理由**：虽然是二分答案，但其中的“移除石头”操作需要循环判断位置，与密钥循环使用的思路有共通性。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者提到在调试时遇到的问题，例如：
</insights_intro>

> 参考经验（来自多位作者）：“一开始忘记处理负数情况，比如密文是`a`，密钥是`b`，直接相减得到-1，导致明文错误。后来通过打印中间变量发现问题，加上`+26`后解决。”

**点评**：这些经验提醒我们，在处理循环问题时，一定要考虑边界情况（如最小值、最大值）。打印中间变量（如偏移量、计算结果）是调试的重要手段，能快速定位错误。

-----

<conclusion>
本次关于“Vigenère密码”的C++解题分析就到这里。希望这份指南能帮助你理解字符处理、模运算和循环逻辑的应用。记住，编程的关键是多思考、多练习，遇到问题时不要怕调试！下次我们再一起挑战新的算法题，加油！💪
</conclusion>

-----

---
处理用时：157.83秒