# [ABC266E] Throwing the Die

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc266/tasks/abc266_e

サイコロを使ったゲームをします。ゲームは最大 $ N $ 回のターンからなり、各ターンは次のように進行します。

- $ 1,\ldots,6 $ の目が等確率で出る $ 6 $ 面ダイスを振り、出目を $ X $ とする(出目は各ターンで独立とする)。
- 現在が $ N $ ターン目なら、**スコア** を $ X $ とし、ゲームを終了する。
- そうでないとき、ゲームを続行するか終了するか選択する。
  - ゲームを終了する場合、スコアを $ X $ とし、残りのターンは行わずにゲームを終了する。

スコアの期待値が最大になるように行動したとき、スコアの期待値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $

## 样例 #1

### 输入

```
1```

### 输出

```
3.5000000000```

## 样例 #2

### 输入

```
2```

### 输出

```
4.2500000000```

## 样例 #3

### 输入

```
10```

### 输出

```
5.6502176688```

# 题解

## 作者：FFTotoro (赞：7)

## 解法

设 $f(i)$ 为到第 $i(1\le i\le n)$ 局游戏时最大分数的期望值；

很显然，第 $i-1$ 轮游戏结束后，下一局游戏 $1,2,3,4,5,6$ 的出现概率均等（记下一局的得分为 $x$），则易得下一局游戏的得分对答案有贡献的充要条件为 $x>f(i)$（否则上一局的分数更高，取上一局的分数）。

这样，我们就很容易推出：

$$
f(i)=\sum\limits_{j=1}^6\frac{1}{6}\max\{f(i-1),j\}
$$

## 实现

递推或递归实现即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; double c=0; cin>>n;
    for(int i=1;i<=n;i++){
        double c0=0;
        for(int j=1;j<=6;j++)c0+=max(c,1.0*j);
        c=c0/6;
    }
    cout<<fixed<<setprecision(9)<<c<<endl;
    return 0;
}
```


---

## 作者：dabenBbx (赞：6)

可以通过分析发现每一次投骰子都要根据上一次结果进行取舍，所以可以推断出这是一道递推题。

### 分析：
   首先我们要知道期望值指的是轮到每次投的时候，所有可能出现的结果加一起除以 $6$。
   
> 为什么除以的是 $6$ 呢？
>
>因为一个骰子有 $6$ 面，每面出现的概率都是 $\displaystyle \frac 1 6$。
  
 其次，想要期望值最大就要进行判断：
 
  如果投出的值比上一次的期望值大，则保留；否则，如果小就直接取上一次的期望值再投即可。
  
注意：

通过样例可以发现结果要保留 $10$ 位小数！！！

------------

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double f[105];//递推数组
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=6;j++){//循环枚举1-6的情况
            if(j>f[i-1]){//比上次大就保留
                f[i]+=j;
            }
            else
            {
                f[i]+=f[i-1];//否则就加上上一次的期望值
            }
        }
        f[i]=f[i]/6;//除以6
    }
    cout<<fixed<<setprecision(10)<<f[n];//保留10位小数
    return 0;
}
```


---

## 作者：williamY (赞：2)

## E
根据题意我们可以得知我们是通过期望 DP 来求解此题的。

那么我们可以想到 $f_i$ 表示第 $i$ 轮的期望。

所以转移方程就会是:

$$
f(i) = \sum_{j=1}^{6}{[j>f(i+1)] \times \frac{j}{6} + [j\le f(i+1)] \times \frac{f(i + 1)}{6}}
$$

好吧，其实逻辑就是：如果这一次的期望大于等于上一次的期望，那就掷，否则就不掷。
然后最后要注意题目要求的是输出保留 $10$ 位小数。
```cpp
#include<bits/stdc++.h>
using namespace std;
double dp[101];
int main(){
    int n;
    cin>>n;
    dp[n+1]=0;
    for(int i=n;i>=1;i--){
        // dp[i]=dp[i+1];
        for(int j=1;j<=6;j++){
            if(j>dp[i+1])dp[i]+=j/6.0;
            else dp[i]+=dp[i+1]/6.0;
        }
    }
    cout<<fixed<<setprecision(10)<<dp[1]<<endl;
}

```

---

## 作者：Epoch_L (赞：2)

## E
期望 dp，$f_i$ 表示第 $i$ 轮的期望，可以枚举这一次掷到的值，如果小于上一次的期望，那就不如不掷，否则就掷。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=1e5+7;
double f[N]; 
main()
{
	int n;
	read(n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=6;j++)
		{
			if(j>f[i-1])
				f[i]+=j;
			else f[i]+=f[i-1];
		}
		f[i]/=6;
	}
	printf("%.10lf",f[n]);
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

显然是一道期望 DP，也容易想到设 $f_i$ 表示抛了 $i$ 次的期望最大值。

对于当前状态，从 1 到 6 枚举抛到的值，注意几种情况的概率是相同的。

接看是抛到的值大还是不抛时的期望大，因为如果抛到的值没有不抛时的期望大就没有必要抛，最后取最大值。

$$
f_i=\frac{1}{6}\sum_{j=1}^6\max(j,f_{i-1}) 
$$

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long double f[1005];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (long double j = 1; j <= 6; j++) {
            if (j <= f[i - 1]) {
                f[i] += f[i - 1] / 6;
            } else {
                f[i] += j / 6;
            }
        }
    }
    printf("%.10LF", f[n]);
}
```

---

## 作者：123456789dd (赞：0)

采用递推的写法。

用 $f_i$ 记录第 $i$ 局游戏结束后的期望。

每局游戏 $1,2,3,4,5,6$ 出现的概率均等，为 $\frac{1}{6}$。

那么如果下一局游戏的得分为 $a$，那么当 $a>f_{i-1}$ 时，才会取这次的得分（否则取上一次的得分）。

那么我们就可以推出：

$$f_i = \sum _ {j = 1} ^ 6 {\frac{1}{6} \max(f_{i-1},j)}$$

现在给出递推代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
double f[100010];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
        {
            if(j>f[i-1]) f[i]+=j;
            else f[i]+=f[i-1];
        }
        f[i]/=6;
    }
    printf("%.10lf",f[n]);
    return 0;
}
```


---

## 作者：Qiu_chen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc266_e)

## 题目大意

你有一个普通均匀的正方体骰子，六个面写有 $1,2,3,4,5,6$。你在玩一个游戏，每次丢骰子之后，你可以：
- 如果这是你的第 $N$ 次投掷，那么你应当结束游戏。
- 否则你可以选择重新投，或者结束游戏。

给定 $N$，计算如果你希望**最后一次投掷**时朝上面的**期望**最大，那么这个期望是多少。

## 题目思路


对于 $f[i]$ 表示游戏进行 $i$ 轮的期望，如果下一轮投的数比期望更大，我们就会投，否则我们不投。

因此获得推导方程（C++）：

```cpp
for(int j=1;j<=6;j++){
	if((double)j>=f[i-1]) //有贡献，投
		f[i]+=1.0*j;  //注意要用1.0来乘
	else f[i]+=f[i-1]; // 无贡献，不投
}
f[i]/=6;
```

不用想得太复杂，就这么简单明了。

## 核心代码

以下为 C++ 核心代码：

```
void solve(){
	cin>>n;
	f[1]=3.5;
	for(int i=2;i<=n;i++){
		int t=0;  //别忘清0
		for(int j=1;j<=6;j++){
			if((double)j>=f[i-1]) //有贡献，投
				f[i]+=1.0*j;  //注意要用1.0来乘
			else f[i]+=f[i-1]; // 无贡献，不投
		}
		f[i]/=6;
	}
	printf("%.10lf\n", f[n]);  //保留后10位
}
```






---

## 作者：_zhx (赞：0)

# AT_abc266_e [ABC266E] Throwing the Die

## 思路

很明显，是一道期望题。因为期望值要最大，且 $1\sim6$ 掷到的概率一样大，所以我们可以用 DP 去做。

设定 DP 数组为 $f$，设 $f_i$ 为最大值。

$$f_i=\frac{1}{6}\sum\limits_{j=1}^6\max(j,{f_i}_{-1})$$

然后再来看是掷骰子期望值大，还是不掷骰子的期望值大，再决定掷不掷。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;long double f[10005];
int main()
{
    scanf("%lld",&n);
    for(long long i=1;i<=n;i++) for(long double j=1;j<=6;j++) if(j<=f[i-1])f[i]+=f[i-1]/6.0; else f[i]+=j/6.0;
    printf("%.10LF\n",f[n]);
    return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/AT_abc266_e)

## 思路

一道期望 DP 题。

设 $f_i$ 为第 $i$ 的期望最大值。

一局中只有 $1,2,3,4,5,6$ 这几种情况。

这几种情况的概率是相同的。

接下来就要看抛到的值是否比不抛时的期望大。

如果抛到的值比不抛时的期望小就没有必要抛，否则就要抛，最后取最大值。

$\displaystyle f_i=\frac{1}{6}\sum^6 _{j=1}\max(j,f_{i-1})$

## 代码

```
#include<bits/stdc++.h>
using namespace std;
long long n;
long double f[10005];
int main()
{
    cin>>n;
    for(long long i=1;i<=n;i++)
	{
        for(long double j=1;j<=6;j++)
		{
            if(j<=f[i-1])f[i]+=f[i-1]/6.0;
			else f[i]+=j/6.0;
        }
    }
    cout<<fixed<<setprecision(10)<<f[n]<<"\n";
    return 0;
}
```


---

