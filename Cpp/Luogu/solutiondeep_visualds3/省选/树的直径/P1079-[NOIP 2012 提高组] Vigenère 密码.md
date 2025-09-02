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
# 💡 Kay的C++算法解析：Vigenère 密码 深入学习指南 💡

<introduction>
  今天我们来一起破解“Vigenère 密码”这道经典的字符串处理题！它曾是NOIP 2012提高组的第一道题，核心是模拟密码的解密过程——就像帮字母士兵们“按命令归位”。本指南会帮你理清规则、掌握关键技巧，还能通过像素动画直观看到每一步操作~
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟与字符串处理  

🗣️ **初步分析**：
> 解决Vigenère密码问题，关键是**“按规则模拟每一步解密”**——就像给每个密文字符发一个“回家的地图”：  
> 1. **密钥循环用**：如果密文比密钥长，密钥要像“循环播放的磁带”一样重复使用（比如密钥是`abc`，密文第4位对应密钥第1位）；  
> 2. **大小写保持**：明文的大小写必须和密文一模一样（密文是大写，明文也大写）；  
> 3. **偏移计算**：把字母转成0-25的数字（A/a=0，B/b=1…Z/z=25），用密文数字减去密钥数字，再加26取模（避免负数），最后转回头字母。  

   - **核心难点**：处理大小写、密钥循环、偏移的边界条件（比如密文数字比密钥小的时候）；  
   - **通用解法**：所有优质题解都围绕“字符转数字→计算偏移→转回字符”展开，区别在于代码的简洁度和封装性；  
   - **可视化设计思路**：用8位像素风格展示“密文字符→密钥字符→明文计算”的流程——每个字符是一个彩色像素块，处理时高亮当前字符，用数字气泡显示偏移计算，最后用“叮”的音效提示完成一步；  
   - **游戏化元素**：设计“字母归位挑战”，每处理完一个字符得1分，全部完成播放胜利音效，像玩FC游戏一样有成就感~

---

## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰性、代码可读性、实践价值**三个维度筛选了3份优质题解，它们各有亮点，适合不同学习阶段的你~
</eval_intro>

**题解一：(来源：ingu，赞487)**
* **点评**：这份题解的代码**短到“惊人”**，却把核心逻辑浓缩到极致！作者用`&31`（二进制`11111`）快速获取字母的“顺序编号”（比如`A`和`a`的后5位都是`00001`，&31后得到1），再用三目运算符处理偏移的边界（如果密文减密钥后为负，就加26）。代码虽短，但每个操作都“精准打击”核心问题，特别适合学习**如何用位运算优化字符处理**。

**题解二：(来源：qhr2023，赞4)**
* **点评**：这题解的**函数设计很贴心**！作者写了一个`m`函数专门处理单个字符的解密，把“大小写判断→数字转换→偏移计算→转回字符”的逻辑封装起来，主函数只需要循环调用。这种“拆分问题”的思路能让代码更易读、易调试，适合学习**如何模块化解决问题**。

**题解三：(来源：3_14，赞0)**
* **点评**：这份题解的**封装最完整**！作者把“字符转数字”“数字转字符”“解密主逻辑”分别写成函数，代码结构像“搭积木”一样清晰。比如`charToNum`函数统一处理大小写字母转0-25的数字，`vigenereDecrypt`函数负责整个解密流程。这种写法特别适合**大型项目或需要复用代码的场景**，能培养良好的编码习惯。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解密Vigenère密码的“拦路虎”主要有三个，解决它们就能“通关”！我们结合优质题解的经验，逐一拆解~
</difficulty_intro>

1.  **关键点1：如何保持明文的大小写？**
    * **分析**：密文的大小写决定明文的大小写——比如密文是`H`（大写），不管密钥是`a`还是`A`，明文必须是大写。优质题解的通用做法是：**先记录密文的大小写状态，再用这个状态转回字符**（比如3_14的`isUpper`变量，qhr2023的条件判断）。
    * 💡 **学习笔记**：大小写是“表面现象”，数字计算是“核心逻辑”——先处理数字，再还原大小写！

2.  **关键点2：如何循环使用密钥？**
    * **分析**：密钥的长度可能比密文短，这时候要用`i % key_len`（`i`是密文的当前位置，`key_len`是密钥长度）来获取对应的密钥字符。比如密钥长度是3，密文第4位对应`4%3=1`（第2个密钥字符）。所有优质题解都用了这个技巧，简单却有效！
    * 💡 **学习笔记**：循环问题找“模运算”，它是“重复使用”的神器~

3.  **关键点3：如何处理偏移的负数？**
    * **分析**：当密文数字比密钥数字小时（比如密文是`A`=0，密钥是`B`=1），直接减会得到-1，这时候要加26再取模（`(0-1+26)%26=25`，对应`Z`）。所有优质题解都用了`+26`的操作，避免负数问题。
    * 💡 **学习笔记**：模运算处理循环问题时，加一个周期（这里是26）再取模，能解决负数！

### ✨ 解题技巧总结
<summary_best_practices>
通过这道题，我们能总结出字符串处理的“通用技巧包”：
</summary_best_practices>
- **技巧1：字符转数字**：用`c - 'A'`（大写）或`c - 'a'`（小写）把字母转成0-25的数字，方便计算；  
- **技巧2：模块化封装**：把重复的逻辑（比如字符转换、解密）写成函数，让代码更清晰；  
- **技巧3：边界处理**：遇到“循环”或“负数”问题，记得用模运算+周期（比如26）解决；  
- **技巧4：大小写保持**：先记录状态（是否大写），再还原，不要让大小写干扰核心计算！

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们先看一份**封装完整、可读性高**的通用实现（来自3_14的题解），它能帮你快速理解整个解密流程~
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：这份代码用函数封装了“字符转数字”“数字转字符”“解密主逻辑”，结构清晰，适合新手学习如何组织代码。
* **完整核心代码**：
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;

    // 将字符转换为0-25的数字（忽略大小写）
    int charToNum(char c) {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        else if (c >= 'a' && c <= 'z') return c - 'a';
        return 0; // 非字母处理（本题不会出现）
    }

    // 将数字转换为字符（根据isUpper决定大小写）
    char numToChar(int num, bool isUpper) {
        return isUpper ? ('A' + num) : ('a' + num);
    }

    // 解密主函数：输入密文和密钥，返回明文
    string vigenereDecrypt(const string& ciphertext, const string& key) {
        string plaintext;
        int keyLen = key.size();
        for (int i = 0; i < ciphertext.size(); ++i) {
            char c = ciphertext[i];
            bool isUpper = (c >= 'A' && c <= 'Z'); // 记录密文大小写
            int cNum = charToNum(c); // 密文转数字
            int kNum = charToNum(key[i % keyLen]); // 密钥转数字（循环使用）
            int mNum = (cNum - kNum + 26) % 26; // 计算明文数字（加26避免负数）
            plaintext += numToChar(mNum, isUpper); // 转回字符并保持大小写
        }
        return plaintext;
    }

    int main() {
        string key, ciphertext;
        cin >> key >> ciphertext;
        cout << vigenereDecrypt(ciphertext, key) << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码分为三个部分：  
    > 1. `charToNum`：把字母转成0-25的数字（不管大小写）；  
    > 2. `numToChar`：把数字转回字母（根据`isUpper`决定大小写）；  
    > 3. `vigenereDecrypt`：循环处理每个密文字符——记录大小写→转数字→取对应密钥→计算偏移→转回字符；  
    > 主函数只需要输入密钥和密文，调用解密函数输出结果。

---
<code_intro_selected>
接下来我们看**ingu的“极简代码”片段**，学习如何用位运算优化字符处理~
</code_intro_selected>

**题解一：(来源：ingu)**
* **亮点**：用`&31`快速获取字母顺序，代码短到“一行核心逻辑”！
* **核心代码片段**：
    ```cpp
    #include <iostream>
    using namespace std;
    int main() {
        string k,c;
        cin>>k>>c;
        for (int i=0;i<c.length();i++) {
            int t=(k[i%k.length()]&31)-1; // 密钥转偏移量（1-25）
            c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26; // 密文减偏移，处理边界
        }
        cout<<c<<endl;
        return 0;
    }
    ```
* **代码解读**：
    > 1. `k[i%k.length()]&31`：`&31`是取二进制后5位——`A`（65=1000001）&31=1，`a`（97=1100001）&31=1，所以不管大小写，都能得到字母的“顺序编号”（1-26）；  
    > 2. `(k[...]&31)-1`：把顺序编号转成偏移量（比如`A`对应0，`B`对应1…`Z`对应25）；  
    > 3. `c[i]&31`：密文转顺序编号（1-26），减偏移量`t`——如果结果>0，直接减`t`（因为`c[i]`是字符，减`t`相当于转成明文）；否则加26（处理边界，比如密文是`A`=1，偏移是2，1-2=-1，加26得25，对应`Z`）。  
    > 是不是很巧妙？用位运算把“大小写转换”和“顺序编号”一步完成！
* 💡 **学习笔记**：位运算能帮你“偷懒”——如果两个字符的二进制某几位相同，可以用`&`提取出来，避免写复杂的条件判断~

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”解密过程，我设计了一个**8位像素风格的动画**——像玩《超级马里奥》一样，每个字母都是一个可爱的像素块，一步一步“归位”！
</visualization_intro>

### ✨ 动画设计方案
* **主题**：字母士兵的“回家之旅”（密文字符→密钥指挥→明文归位）  
* **风格**：FC红白机风格（8位像素、16色调色板、复古字体）  
* **核心演示内容**：  
  1. **初始界面**：屏幕左侧是密文字符串（蓝色像素块，比如`H e l l o`），右侧是密钥字符串（绿色像素块，比如`a b c`），中间是“计算区”（显示数字和偏移）；  
  2. **单步执行**：点击“下一步”，当前密文字符（黄色高亮）和对应密钥字符（绿色闪烁）移动到计算区：  
     - 密文`H`→转数字`7`（蓝色气泡显示）；  
     - 密钥`a`→转数字`0`（绿色气泡显示）；  
     - 计算`7-0=7`→转明文`H`（红色像素块显示）；  
  3. **边界处理演示**：比如密文`A`（数字`0`）和密钥`B`（数字`1`），计算`0-1+26=25`→转明文`Z`（红色块闪烁，播放“叮”的音效）；  
  4. **密钥循环**：当密文处理到第4位时，密钥回到第1位（绿色块循环滚动，显示`a→b→c→a`）；  
  5. **胜利状态**：所有字符处理完成，明文串（红色块）从左到右滚动，播放FC风格的胜利音乐（比如《超级马里奥》的通关音效）。

* **交互设计**：  
  - 控制面板：“开始/暂停”“单步”“重置”按钮（像素风格图标）；  
  - 速度滑块：调整自动播放的速度（从“慢”到“快”）；  
  - AI演示：点击“AI自动解密”，动画自动完成所有步骤，像“AI玩游戏”一样。

* **技术实现**：  
  - 用HTML5 Canvas绘制像素块（每个字符是16x16的像素矩阵）；  
  - 用JavaScript处理动画逻辑（比如`requestAnimationFrame`实现帧动画）；  
  - 用Web Audio API播放音效（“叮”是8位正弦波，胜利音乐是预录的FC风格音频）。

<visualization_conclusion>
通过这个动画，你能**直观看到每个字符的“旅行路线”**——从密文到密钥，再到明文，每一步都“看得见、听得着”。就像玩游戏一样，解密的过程会变得超有趣！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是**“字符循环处理+偏移计算”**，这种思路能解决很多字符串问题。我们来看看它的“变种”~
</similar_problems_intro>

### 🌟 通用思路迁移
* **场景1**：字符加密（比如把明文转密文，只需要把“减密钥”改成“加密钥”）；  
* **场景2**：循环字符串匹配（比如判断一个字符串是否是另一个的循环子串）；  
* **场景3**：字符替换（比如用密钥指定每个字符的替换规则）。

### 📚 洛谷练习推荐
1. **洛谷 P1097** - 统计数字字符个数  
   * 🗣️ **推荐理由**：练习“字符遍历+条件判断”，巩固对字符ASCII码的理解。  
2. **洛谷 P1102** - 字符加密  
   * 🗣️ **推荐理由**：Vigenère密码的“反向问题”（明文转密文），练习偏移计算的逆向思维。  
3. **洛谷 P1598** - 字符串处理  
   * 🗣️ **推荐理由**：练习“循环处理字符串”，类似密钥循环的逻辑。  
4. **洛谷 P2550** - 字符串匹配  
   * 🗣️ **推荐理由**：练习“循环使用模式串”，巩固`i%len`的技巧。

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
很多题解作者分享了自己的“踩坑经历”，这些都是宝贵的经验！
</insights_intro>

> **参考经验 (来自 ingu)**：“我一开始用`c[i] - 'A'`处理大小写，结果发现要写两个条件判断，后来想到`&31`能统一处理，代码瞬间变短了！”  
> **点评**：这位作者的经验告诉我们——**多观察字符的二进制特征**，能找到更简洁的处理方式！比如`A`和`a`的后5位相同，用`&31`就能“一键获取”顺序编号，避免写复杂的`if-else`。

> **参考经验 (来自 3_14)**：“我一开始没封装函数，代码写得很乱，后来拆分成`charToNum`和`numToChar`，调试的时候轻松多了！”  
> **点评**：模块化封装不仅能让代码更清晰，还能**减少重复代码**——比如“字符转数字”的逻辑只需要写一次，不用在多个地方重复写。

---

<conclusion>
Vigenère密码是一道“入门级但很经典”的字符串题，核心是**“按规则模拟每一步”**。通过这道题，你能掌握字符处理、模运算、模块化封装等重要技巧——这些技巧会伴随你解决更多复杂的字符串问题！  
记住：编程就像解密，只要理清规则、拆解问题，再难的题也能“破解”~ 下次我们再一起挑战更有趣的算法！💪
</conclusion>

---

---
处理用时：110.27秒