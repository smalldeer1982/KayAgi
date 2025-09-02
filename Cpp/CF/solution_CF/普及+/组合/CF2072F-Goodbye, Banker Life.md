# Goodbye, Banker Life

## 题目描述

怪物正在逼近城市，为了保护它，Akito 必须在城市周围创建一个防护场。众所周知，防护场有不同的等级。Akito 选择了等级为 $n$ 的防护场。为了构建这个防护场，需要一个特殊咒语，即伟大魔法三角（表示为二维数组 $T$）的第 $n$ 行。我们将这个数组称为 $T$。

魔法三角的定义如下：

- 第 $i$ 行包含 $i$ 个整数。
- 第一行唯一的整数是 $k$。
- 设第 $i$ 行第 $j$ 个元素为 $T_{i,j}$，则：

$$
T_{i,j} = \begin{cases} 
T_{i-1,j-1} \oplus T_{i-1,j}, & \text{if } 1 < j < i \\ 
T_{i-1,j}, & \text{if } j = 1 \\ 
T_{i-1,j-1}, & \text{if } j = i 
\end{cases}
$$

其中 $a \oplus b$ 表示整数 $a$ 和 $b$ 的按位异或运算。

请帮助 Akito 在怪物抵达城市前找到这个无限魔法三角的第 $n$ 行整数。

## 说明/提示

在第一个示例中，根据定义，伟大魔法三角的第一行为 $[5]$。

在第二个示例中，$T_{2,1} = T_{1,1} = 10$ 且 $T_{2,2} = T_{1,1} = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 5
2 10
3 16
9 1
1 52```

### 输出

```
5
10 10
16 0 16
1 0 0 0 0 0 0 0 1
52```

# 题解

## 作者：zyb_txdy (赞：6)

### 题意

给定两个正整数 $n$ 和 $k$，对于 $1 \le j \le i \le n$，定义

$f_{i, j} = \begin{cases} f_{i - 1, j} & j = 1 \\ f_{i - 1, j - 1} & j = i \\ f_{i - 1, j - 1} \bigoplus f_{i - 1, j} & 1 < j < i \end{cases}$

其中，$\bigoplus$ 表示异或运算。特别地，当 $i = j = 1$ 时，$f_{i, j} = k$。

现给定 $n$，$k$，要求 $a_i, a_2 \dots a_n$ 的值。

数据范围：$1 \le n \le 10^6$，$1 \le k < 2^{31}$。

### 分析

感觉，这题，真的超级厉害啊！

首先，$f_{i, j}$ 显然只可能是 $0$ 或 $k$，故只需判断 $f_{i, j}$ 是否为 $0$ 即可得到 $f_{i, j}$ 的值。
因此，下文将默认 $f_{1, 1} = 1$。

打表并找规律可以得出一些神秘做法，这里不讲。

对于这个问题，一个想法是，因为异或就是二进制下的不进位加法，所以我们可以把 $f_{i, j} = f_{i - 1, j - 1} \bigoplus f_{i - 1, j}$ 转换为 $f_{i, j} = f_{i - 1, j - 1} + f_{i - 1, j}$，并把问题转换为判断 $f_{i, j}$ 的奇偶性。

注意到转换后的 $f_{i, j}$ 是杨辉三角。也就是说，对于 $f_{i, j}$，它的值就是 $\begin{pmatrix} i - 1 \\ j - 1 \end{pmatrix} \bmod 2$ 的值。

可以发现，我们可以用 Lucas 定理来干这个事情。众所周知，Lucas 定理说的是：

$$ \begin{pmatrix} n \\ m \end{pmatrix} \bmod p = \begin{pmatrix} \left\lfloor \frac{n}{p} \right\rfloor \\ \left\lfloor \frac{m}{p} \right\rfloor \end{pmatrix} \times \begin{pmatrix} n \bmod p \\ m \bmod p \end{pmatrix} \bmod p$$

也就是说，$f_{i, j}$ 为偶数，当且仅当对 $\begin{pmatrix} i - 1 \\ j - 1 \end{pmatrix}$ 用 Lucas 时，某次运算时满足 $(i - 1) \bmod 2 = 0$ 且 $(j - 1) \bmod 2 = 1$。这个东西显然就是存在一个二进制位，满足 $j - 1$ 在这位上为 $1$，而 $i - 1$ 在这位上为 $0$。也就是 $(i - 1) \& (j - 1) \ne j - 1$，其中 $\&$ 表示与运算。

因此，我们就有 $f_{i, j} = k \times [(i - 1) \& (j - 1) = j - 1]$。用它直接计算每一项的值即可，时间复杂度 $O(n)$。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int T, n, k;

void Solve() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cout << (((n - 1) & (i - 1)) == i - 1 ? k : 0) << " ";
	cout << "\n";
}

signed main() {
	cin >> T;
	while (T--) Solve();
	return 0;
}
```

---

## 作者：PaperBacon (赞：2)

# [CF2072F Goodbye, Banker Life](https://www.luogu.com.cn/problem/CF2072F) 题解

## 题目大意
给定初始值 $k$ 的三角阵，求第 $n$ 行的所有元素。三角阵的生成规则如下：
- 当元素位于行首时：继承正上方元素
- 当元素位于行尾时：继承左上方元素
- 其他位置：等于左上方与正上方元素的异或值
## 解题思路
### 关键性质
通过观察/打表发现，第 $n$ 行第 $j$ 个元素的值由组合数奇偶性决定：
$$
T_{n,j} = 
\begin{cases} 
k & \text{当 } \dbinom{n-1}{j-1} \text{ 为奇数} \\
0 & \text{否则}
\end{cases}
$$
### 数学证明
根据 $p=2$ 时的 **Lucas 定理** ，组合数 $\dbinom{n-1}{j-1}$ 为奇数当且仅当：在二进制表示下，$j-1$ 的每一位都不超过 $n-1$ 对应位的值。  
等价于下面这个组合数奇偶性结论：
$$ (j-1) \ \& \ (n-1) = j-1 $$
如果你没有听说过什么是 **Lucas 定理**，那么你可以阅读 [Lucas 定理-OI Wiki](https://oi-wiki.org/math/number-theory/lucas/) 这篇参考资料。


## 代码实现
```cpp
#include "bits/stdc++.h"
#define vtr vector
#define pb push_back
using namespace std;

void solve(){
	int n,k;cin >> n >> k;
    int mask = n - 1;
    vtr<int> res;
    for(int j = 1;j <= n;++j){
        int pos = j - 1;
        res.pb((pos & mask) == pos ? k : 0);
    }
    for(int i = 0;i < res.size();++i){
        if(i > 0) cout << ' ';
        cout << res[i];
    } cout << '\n';
}

int main(void){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int _ = 1;cin >> _;
	while (_--)solve();
	return 0;
}
```

---

## 作者：_O_w_O_ (赞：1)

我们发现整个矩阵只含有 $0,k$，那么我们不妨把 $k$ 看做 $1$。

我们发现 $T_{i,j}$ 为杨辉三角第 $i$ 行第 $j$ 列的奇偶性，根据二项式定理，有 $T_{i,j}={i-1\choose j-1}$。

看到组合数，考虑 Lucas 定理，那么就有 $T_{i,j}={i-1\choose j-1}\bmod 2={\lfloor\frac{(i-1)}2\rfloor\choose\lfloor\frac{(j-1)}2\rfloor}\times {(i-1)\bmod 2\choose (j-1)\bmod 2}\bmod 2$。

我们注意到 ${i-1\choose j-1}\bmod 2$ 为偶数当且仅当存在一次递归满足 $(i-1)\bmod 2=0$ 且 $(j-1)\bmod 2=1$ 那么很显然等价于 $(i-1)\&(j-1)\neq j-1$。

那么就有 $T_{i,j}=k\times [(i-1)\&(j-1)\neq j-1]$。

code：<https://codeforces.com/contest/2072/submission/309466140>。

---

## 作者：wmrqwq (赞：1)

这是一篇视频题解。

![](bilibili:BV1fHP3ewES9?t=213)

[代码链接](https://codeforces.com/contest/2072/submission/307825594)

---

## 作者：AK_400 (赞：0)

显然，整个三角中只有可能出现 $0$ 和 $k$，于是我们令 $f_{1,1}=1$。

注意到这样 $f_{i,j}$ 就表示杨辉三角对应位置的奇偶性，即 $C_{i-1}^{j-1}\bmod 2$。

考虑一般求组合数的方法，即预处理阶乘，但我们没有办法取模，得想办法不让它太大。

这里我们只需要知道奇偶性，于是我们预处理阶乘中因数 $2$ 的个数，最后计算所求组合数中因数 $2$ 的个数即可。

这里介绍一个内建函数：`__builtin_ctz`，表示二进制下右起 `0` 的个数，等价于因数 $2$ 的个数。

code：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read(a),read(b),read(c)
#define read4(a,b,c,d) read(a),read(b),read(c),read(d)
#define read5(a,b,c,d,e) read(a),read(b),read(c),read(d),read(e)
#define read6(a,b,c,d,e,f) read(a),read(b),read(c),read(d),read(e),read(f)
int fact[1000005];
void init(){
    fact[0]=0;
    for(int i=1;i<=1000000;i++)fact[i]=fact[i-1]+__builtin_ctzll(i);
}
int n,k;
int C(int x,int y){
    return fact[x]-fact[y]-fact[x-y];
}
void slv(){
    read2(n,k);
    for(int i=0;i<n;i++){
        cout<<(C(n-1,i)==0?k:0)<<" ";
    }
    cout<<endl;
}
signed main(){
    init();
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：cwxcplh (赞：0)

前言：怎么说呢，这道题说简单也不简单，说难也不难，简单到找规律也可以写出来，难到不想找规律几乎想不出来……

题目简化：没什么好简化的，题目已经说的很清楚了，就是求一个表的第 $n$ 行的数字，这个表满足下列条件：

- 第 $i$ 行包含 $i$ 个整数。

- 第一行唯一的整数是 $k$。

- 设第 $i$ 行第 $j$ 列的数为 $T_{i,j}$，则：

$$T_{i,j}=\begin{cases}T_{i-1,j-1}\oplus T_{i-1,j}&1\lt j\lt i\\T_{i-1,j}&j=1\\T_{i-1,j-1}&j=i\end{cases}$$

~~突然发现讲着讲着好像复述了一遍题目。~~

看到这道题，我首先得想法就是找规律。请看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/z06rg9ql.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

这里是我列了 $12$ 行后的图，不难发现：每一行都是对称的，但规律并不是很明显，你们也可以尝试着自己多列几个看看能不能找出规律。

因此，我们就不得不采取第二种方法：算正解。我是这样想的。

因为题目中有异或，而跟异或相关的有一个东西：加法。只不过它是没有进位的加法。这里又有个图表，所以我立马想到了杨辉三角。所以我先对这个图的每一个点都除以一个 $k$，这样就成了一个 01 序列，更方便我们理解后面的东西。

然后我们就可以把杨辉三角带进去了，杨辉三角满足 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j}$，跟题目中的一个条件很像，正好也能说明这个思路大概率是对的。但整个图表只有 0 和 1，没有其他的数，这咋办呢？

这也很简单：对杨辉三角的每个数 $\bmod2$ 就行了。事实证明这样做也能得到原来的 01 序列。

我们又知道杨辉三角的每一项为 $C_{j-1}^{i-1}$，带入可得第 $i$ 行第 $j$ 列的数是：

$$f_{i,j}=C_{j-1}^{i-1}\bmod2$$

又根据 Lucas 定理（$C_n^m\bmod p=C_{\lfloor\frac{n}{p}\rfloor}^{\lfloor\frac{m}{p}\rfloor}\times C_{n\bmod p}^{m\bmod p}\bmod p$）可知：

$$f_{i,j}=C_{\frac{j-1}{2}}^{\frac{i-1}{2}}\times C_{(j-1)\bmod2}^{(i-1)\bmod2}\bmod2$$

因为 $1$ 的情况不好算，所以我们来看 $0$ 的情况。

如果上面那个式子是 $0$，说明两项之积为偶数，但当我们把前面不断拆分之后就会发现只有当 $C_{(j-1)\bmod2}^{(i-1)\bmod2}$ 为偶数时才成立，而 $C_{(j-1)\bmod2}^{(i-1)\bmod2}$ 为偶数的情况只有一种：$C_{(j-1)\bmod2}^{(i-1)\bmod2}=0$。由此可知：当 $(i-1)\bmod2=0$ 且 $(j-1)\bmod2=1$ 时，上述条件才成立（因为没有 $C_0^0$ 这个东西），这说明 $i-1$ 和 $j-1$ 在二进制内必然有一位不等，与运算一下就可知，其中 $\&$ 表示与运算：

$$(i-1)\&(j-1)\not=j-1$$

那么把上述条件反过来就是等于 $1$ 的情况。

最后把先开始除以的 $k$ 乘回去就可以得到：

$$f_{i,j}=k\times[(i-1)\&(j-1)=j-1]$$

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cout<<(((i-1)&(n-1))==i-1?k:0)<<" ";//带入公式
        }
        cout<<endl;
    }
    return 0;
}
```

---

