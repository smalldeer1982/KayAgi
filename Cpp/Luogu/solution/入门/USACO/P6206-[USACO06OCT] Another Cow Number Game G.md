# [USACO06OCT] Another Cow Number Game G

## 题目描述

奶牛们在玩一种数字游戏，Bessie 想让你帮她预测一下结果。游戏开始时，Bessie 将得到一个正整数 $N$。此时她的分数为 $0$。

奶牛们按照以下规则对 $N$ 进行变换：

- 如果 $N$ 是奇数，那么将它乘以 $3$ 后再加 $1$。
- 如果 $N$ 是偶数，那么将它除以 $2$。

数字每变换一次，Bessie 就得到 $1$ 分。当 $N=1$ 时，游戏结束。此时的分数就是她的最终得分。

## 说明/提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le N\le 10^6$。

------------

**【样例说明】**

当 $N$ 的初始值为 $5$ 时，游戏的过程如下：

| $N$ | 变换后的数字 | 变换过程 | 总分 |
| :----------: | :----------: | :----------: | :----------: |
| $5$ | $16$ | $3\times 5+1$ | $1$ |
| $16$ | $8$ | $16\div 2$ | $2$ |
| $8$ | $4$ | $8\div 2$ | $3$ |
| $4$ | $2$ | $4\div 2$ | $4$ |
| $2$ | $1$ | $2\div 2$ | $5$ |

Bessie 的最终得分为 $5$。


## 样例 #1

### 输入

```
5```

### 输出

```
5```

# 题解

## 作者：chenyilai (赞：14)

这就是一道很简单的[角谷猜想](https://baike.baidu.com/item/%E5%86%B0%E9%9B%B9%E7%8C%9C%E6%83%B3?fromtitle=%E8%A7%92%E8%B0%B7%E7%8C%9C%E6%83%B3&fromid=5213440)，又称冰雹猜想。我们只需根据题意模拟，再用一个变量记录就行了。

贴上附了注释的AC代码~~别问我为什么0202年了还有P党~~
```pas
var n,sum:int64;
begin
  readln(n);
  while n<>1 do//重复直到游戏结束
  begin
   inc(sum);//记录次数
   if n mod 2=0 then n:=n div 2//判断奇偶
    else n:=n*3+1;
  end;
  writeln(sum);//输出答案
end.
```
如果你是C党，请看这里：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum;
int main(){
   scanf("%lld",&n);
   while (n!=1){//重复直到游戏结束
      sum++;//记录次数
      if (n%2==0) n/=2;//判断奇偶
      else n=n*3+1;
   }
   cout<<sum;//输出答案
   return 0;
}
```
关于角谷猜想的题目，还有[【深基5.例3】冰雹猜想](https://www.luogu.com.cn/problem/P5727)。

---

## 作者：wmy_goes_to_thu (赞：5)

没人写题解？我写！

暴力呗，每次判断进行更新即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int a,ans=0;
  cin>>a;
  while(a^1)
  {
    ans++;
    if(a&1)a=a+(a<<1)+1;
    else a=a>>1;
  }
  cout<<ans;
}
```

---

## 作者：do_while_false (赞：5)

【大概思路】

首先我们可以得到一个边界条件: $n\neq1$

对于一个 $n\neq1$ ，我们有 $n=\begin{cases}x \times 3+1&x\mod2=1\\x\div 2&x\mod2=0\end{cases}$ 

根据这个公式模拟即可,每次循环使计数器加一，当 $n=1$ 时，退出循环。

【代码实现】

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans; 
inline long long read() {//快读 
	long long r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
inline void write(long long x) {//快输 
	char ch[40];int len=0;
	if(x<0){putchar(45);x=~x+1;}
	do{ch[len++]=x%10+48;x/=10;}while(x>0);
	for(int i=len-1;i>=0;i--) putchar(ch[i]);
	putchar('\n');
}
int main(void) {
	n=read();
	while(n!=1) {//边界条件 
		if(n%2==1) n=n*3+1;//公式 
		else n/=2;
		ans++;//计数器+1 
	}
	write(ans);
	return 0;
}

```

---

## 作者：HsKr (赞：4)

**UPDATE:新加了几组数据，发现之前的过不了了，更改一下。**

按照题意模拟即可。

要开long long。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
	long long n,score=0;//定义变量：n为输入的数，score为得分。 
	cin>>n;//输入n 
	while(n!=1){//当 N=1时，游戏结束
		if(n%2==1) n=n*3+1;//如果 N 是奇数，那么将它乘以 3 后再加 1。 
		else n/=2;//如果 N 是偶数，那么将它除以 2。
		score++;//数字每变换一次，Bessie 就得到 1 分。
	}
	cout<<score<<endl;//输出最终得分 
	return 0;
}

```

---

## 作者：迷残云 (赞：3)

~~一道水题，来水个题解~~

这道题，是举世闻名的难题（真）：在国际上有很多名字，因为他有太多名字，所以……统一改名叫$ 3x+1 $猜想。。最后证明的是$ n $一定会变成$ 1 $,
如果你会证明，请私信楼主，我会将我的膝盖送给你


但是……跟这题有什么关系呢……这题直接模拟就可。。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans=0;
int main()
{
	scanf("%d",&n);
	while(n!=1)
	{
		if(n%2==0)n/=2;
		else n=n*3+1;
		ans++;
	}
	printf("%d",ans);
	return 0;
}
```


---

