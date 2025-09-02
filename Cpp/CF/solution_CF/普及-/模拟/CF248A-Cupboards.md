# Cupboards

## 题目描述

One foggy Stockholm morning, Karlsson decided to snack on some jam in his friend Lillebror Svantenson's house. Fortunately for Karlsson, there wasn't anybody in his friend's house. Karlsson was not going to be hungry any longer, so he decided to get some food in the house.

Karlsson's gaze immediately fell on $ n $ wooden cupboards, standing in the kitchen. He immediately realized that these cupboards have hidden jam stocks. Karlsson began to fly greedily around the kitchen, opening and closing the cupboards' doors, grab and empty all the jars of jam that he could find.

And now all jars of jam are empty, Karlsson has had enough and does not want to leave traces of his stay, so as not to let down his friend. Each of the cupboards has two doors: the left one and the right one. Karlsson remembers that when he rushed to the kitchen, all the cupboards' left doors were in the same position (open or closed), similarly, all the cupboards' right doors were in the same position (open or closed). Karlsson wants the doors to meet this condition as well by the time the family returns. Karlsson does not remember the position of all the left doors, also, he cannot remember the position of all the right doors. Therefore, it does not matter to him in what position will be all left or right doors. It is important to leave all the left doors in the same position, and all the right doors in the same position. For example, all the left doors may be closed, and all the right ones may be open.

Karlsson needs one second to open or close a door of a cupboard. He understands that he has very little time before the family returns, so he wants to know the minimum number of seconds $ t $ , in which he is able to bring all the cupboard doors in the required position.

Your task is to write a program that will determine the required number of seconds $ t $ .

## 样例 #1

### 输入

```
5
0 1
1 0
0 1
1 1
0 1
```

### 输出

```
3
```

# 题解

## 作者：Node_Edge (赞：3)

**题意化简：**

给定两个 $01$ 构成的数组，**分别**使得它们全变为 $1$ 或者 $0$，求最小操作次数。

**思路分析：**

对于其中一个数组，想要最小操作次数，看是 $0$ 更少还是 $1$ 更少，哪个少变哪个，操作次数就是更少的那个数的个数，最后两个数组的最小操作次数的和就是答案。

**代码分享：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[10005],y[10005],a,b;
int main(){
    cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    for(int i=1;i<=n;i++){
        if(x[i]==0) a++;//看 0 更少还是 1 更少
        if(y[i]==0) b++;
    }
    cout<<min(a,n-a)+min(b,n-b);//两个数组的最小操作次数的和
    return 0;
}
```

- $2022$ 年 $8$ 月 $10$ 日修正代码错误

---

## 作者：yydfj (赞：2)

**这是本蒟蒻第十八次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你两个长度为 $n$ 数组 $x$ 和数组 $y$，它们里面的元素只包含 $0$ 和 $1$，现在需要将它们里面的元素分别统一，问最少要改变多少个元素。

## 解法综述

设 $a$ 为数组 $x$ 里的元素出现 $1$ 的数量，设 $b$ 为数组 $y$ 里的元素出现 $1$ 的数量，则 $n-a$ 为数组 $x$ 里的元素出现 $0$ 的数量，$n-b$ 为数组 $y$ 里的元素出现 $0$ 的数量。

由此可以得出使数组 $a$ 元素统一最少改变元素为 $a$ 和 $n-a$ 的最小值，使数组 $a$ 元素统一最少改变元素为 $b$ 和 $n-b$ 的最小值，最终答案为 ``min(n-a,a)+min(n-b,b)``。

## 代码描述
```cpp
#include<cstdio>
#define min(a,b) (a<b?a:b)
int n,x,y,a,b;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		if(x) a++;
		if(y) b++;
		//因为x和y可以及时处理，所以不需要定义x和y为数组
	}
	printf("%d",min(n-a,a)+min(n-b,b));
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 题目

[题目传送门](https://www.luogu.com.cn/problem/CF248A)

简述：给定你两个长度为 $n$ 的 $01$ 序列，让你改变最少的元素使得序列中的元素统一。

### 思路

首先循环输入两个序列，在输入的同时进行累加，这样累加出来就是序列中 $1$ 的个数。然后判断序列中是 $1$ 的个数多还是 $0$ 的个数多。最后得出来的结果即为最少需要改变的元素的个数。

在判断时，我们也可以使用 $\min$ 函数。$\min(a,b)$ 就是在 $a$ 和 $b$ 中取最小值。由于我们累加的是 $1$ 的个数，所以 $0$ 的个数就是 $n$ 减去 $1$ 的个数。设序列 $x$ 中 $1$ 的个数为 $k$，序列 $y$ 中 $1$ 的个数为 $m$，我们就能得出来一个公式：$\min(n-a,a) + \min(n-m,m)$，即为最终结果。

### 代码


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
int n,x[100001],y[100001];
int ansx=0,ansy=0; //x和y中1分别的个数
//int rl=0;
void kt(){ //累加函数
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i];
        ansx+=x[i],ansy+=y[i];
    }
}
signed main(){ //由于上面int定义为long long了，所以这里主函数不能用int定义，而是signed
    kt(); //使用函数
    cout<<min(n-ansx,ansx)+min(n-ansy,ansy); //公式
    return 0;
}
```



---

## 作者：XKqwq (赞：1)

## 题意

有一个类似下面的表格，长度为 $n$ ，里面只有 $0$ 和 $  1$ 。

| 0 | 1 |
| :----------: | :----------: |
| 1 | 0 |
| 0 | 1 |
| 1 | 1 |
| 0 | 1 |
| ... | ... |

然后我们要把它变成每一边都一样（像下面的表格）：

| 0 | 1 |
| :----------: | :----------: |
| 0 |  1|
| 0 | 1 |
| 0 |  1|
| 0 |  1|
| ... | ... |


求改变数字的最小次数。



## 解法

因为最终的情况只有 $2$ 种，我们可以算出每一种解法所需的次数，然后用 $\min()$ 取最小值即可。

我们定义 $4$ 个变量分别表示：左边 $0$ 的个数 $t_1$，左边 $1$ 的个数 $t_2$ ，右边 $0$ 的个数 $t_3$ ，右边 $1$ 的个数 $t_4$ 。分别求出两边的最小值，然后相加即可。（顺便希望更正一下翻译， `另一边的门与之相反` 这句错误，删掉就可以）



## $\texttt{ Code: }$

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
#define R read()
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){ if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9'){ x=x*10+ch-48; ch=getchar(); }
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

int n,a=0,b=0,t[4];
int main(){
	n=read();
	while(n--){
		a=R,b=R;
		t[a]++;
		t[b+2]++;
	}
	write(min(t[0],t[1])+min(t[2],t[3]));
	return 0;
}

```

**提示：抄题解是不可取的。**

---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意

有一个走廊，左右都有 $n$ 扇门，要么是看开着的，要么是关着的，将左右两列的门都变为一样的状态的最小值。

## 思路

看每列的门的哪种状态更小，这就是将那列的门都变为一样的状态的最小值；

最后相加即可。

## 代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10005;
int n, a[N], b[N], asum[N], bsum[N];
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i] >> b[i];
		asum[a[i]]++; // 每个状态的值
		bsum[b[i]]++;
	}
	cout << min(asum[0], asum[1]) + min(bsum[0], bsum[1]); // 最小值的总和
	return 0;
}

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF248A)

这道题其实就是要让我们找这两列各有几个 $0$ 和 $1$，因为我们要让每列的数字都相同，且改变次数要少，那么我们统计出每列的 $0$ 与 $1$ 的个数后，要改变的次数就变成了每列当中 $0$ 与 $1$ 的个数的最小值，再把最小值加入进总的改变次数的值就结束了。

------------
# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,s1=0,s2=0,s=0;
int main()
{
	scanf("%d",&n);
	for(register int i=0;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		if(!x) s1++;
		if(!y) s2++;
	}
	s+=min(n-s1,s1);
	s+=min(n-s2,s2);
	printf("%d",s);
	return 0;
}
```


---

## 作者：jimmyfj (赞：0)

本题思路 : 先分别统计出左边所有的门和右边所有的门的开关状态，再求出两边所需改变门的状态的最小值 $al$ 和 $ar$。最后将左边和右边的最小值加起来，得出的就是改变所有门的状态的最小次数。

下面讲解如何求两边改变门的状态的最小值 $al$ 和 $ar$ :

将每次输入的每一个位置左边和右边的门的状态记为 $l$，$r$。( 注 : $ox$ 为左边的门开着的数量，$cx$ 为左边的门关着的数量；$oy$ 为右边的门开着的数量，$cy$ 为右边的门关着的数量 )

左边的情况 :

1. 如果 $l = 0$，则 $ox + 1$。

2. 如果 $l = 1$，则 $cx + 1$。

右边的情况 :

1. 如果 $r = 0$，则 $oy + 1$。

2. 如果 $r = 1$，则 $cy + 1$。

最小值 :

$al = \min \left(ox, oy\right)$

$ar = \min \left(cx, cy\right)$

参考代码 : 
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n;
int l, r;
int al, ox, cx;
int ar, oy, cy;
int main()
{
	scanf("%d", &n);
	while(n --)
	{
		scanf("%d %d", &l, &r);
		if(l == 0) ox ++;//左边的情况1
		else cx ++;//左边的情况2
		if(r == 0) oy ++;//右边的情况1
		else cy ++;//右边的情况2
	}
    //求al, ar的最小值
	if(ox > oy) o = oy;
	else al = ox;
	if(cx > cy) c = cy;
	else ar = cx;
	printf("%d\n", al + ar);//改变所有门的状态的最小次数
	return 0;
 } 
```

---

## 作者：abensyl (赞：0)

## [原题传送门](https://www.luogu.com.cn/problem/CF248A)

## 思路

为保持门的开关状态整齐，应使其都开或都关闭，所以如果某一侧关闭的数量比打开的数量少，我们便将原本关闭的门打开，否则全部关闭，所以答案即为左侧门开着的数量与左侧门关着的数量的较小的一个加右侧门开着的数量与右侧门关着的数量的较小的一个，即 $\min (a,n-a) + \min (b,n-b)$。


## 代码

```cpp
#include<bits/stdc++.h>
int n,m,a,b; 
int main() {
	scanf("%d",&n);=
	for(int i=1;i<=n;i++) {
		scanf("%d",&m); 
		if(m) a++; //a表示左侧门开着的数量，如果输入为1，左侧门开着的数量加一 
		scanf("%d",&m); 
		if(m) b++; //a表示右侧门开着的数量，如果输入为1，右侧门开着的数量加一 
	}
	int ans=min(a,n-a)+min(b,n-b); 
	//答案即为左侧门开着的数量与左侧门关着的数量的较小的一个加右侧门开着的数量与右侧门关着的数量的较小的一个
	printf("%d",ans); 
	return 0; //养成好习惯 
}
```


---

## 作者：chlchl (赞：0)

## 题意简述
有 $2n$ 个数，每个数是 $0$ 或 $1$。问最少要改多少个数，使得每一列的数都相同。

## 做法
非常基础的一道题，可以在 $O(1)$ 的复杂度搞定（除去读入）。

因为一共只有两列，所以开两个数组，$l_i$ 记录左边一列 $i$ 的个数，$r_i$ 记录右边一列 $i$ 的个数，读入时记录。

因为要求最小操作次数，又注意到只有 $0$ 和 $1$，所以我们取 $\min(l_0,l_1)+\min(r_0,r_1)$，代表左边一列数量较小的数和右边一列数量较小的数的和（把他们替换成另一个数），就是最小的操作次数啦！

非常简单，适合萌新，建议降红。

## 代码
以下是参考代码。珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, lx, rx, l[2], r[2];

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%d%d", &lx, &rx);
		l[lx]++, r[rx]++;//开数组方便，不用像其他题解一样判断
	}
	printf("%d\n", min(l[0], l[1]) + min(r[0], r[1]));//上面讲的公式
	return 0;
} 
```


---

## 作者：·糯· (赞：0)

## 题目分析
这题我们发现，左边最少需要变的数的个数就是左边的 0 和 1 中较少的那个（就把较少的那些数变成较多的那些数），右边的也是同样，所以其实答案就是左边数较少的数与右边数较少的数之和。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,lt[10010],rt[10010],suml0,suml1,sumr0,sumr1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>lt[i]>>rt[i];
		if(lt[i]==0)
			suml0++;//左边0的个数
		else if(lt[i]==1)
			suml1++;//左边1的个数
		if(rt[i]==0)
			sumr0++;//右边0的个数
		else if(rt[i]==1)
			sumr1++;//右边1的个数
	}
	printf("%d\n",min(suml0,suml1)+min(sumr0,sumr1));//左边较少的数与右边较少的数之和
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
在一个走廊上有 $2n$ 扇门，排成两列分居左右。有个人很无聊，随意地开关了一些门，使得这些门看起来十分乱。现在请开关一些门，使得这些门恢复原来整齐的状态（要么都开、要么都关、要么一边的 $n$ 扇门都开，另一边的 $n$ 扇门都关）。求最少需要操作的次数。

**数据范围：$2\leqslant n\leqslant 10^4$。**
## Solution
只需要枚举使得 $2n$ 扇门整齐的四种情况需要操作的次数，再取最小值即可。
## Code
```cpp
int main() {
	getint(n);
	_for(i, 1, n)	getint(l[i]), getint(r[i]);
	_for(i, 1, n)	ans1 += (1 - l[i]) + r[i], ans2 += l[i] + (1 - r[i]), ans3 += l[i] + r[i], ans4 += (1 - l[i]) + (1 - r[i]);
	ans = min(ans1, min(ans2, min(ans3, ans4)));
	writeint(ans);
	return 0;
}
```

---

## 作者：xgwpp6710 (赞：0)

~~无耻推销一波 [My blog](/blog/250940/)~~

# 下面进入正题

分析一下题目（这题实际上是很水的，个人建议降红），其实就是给你两个 $01$ 数组 $x,y$ ，让你求这两个数组中较少的数字的数量之和。

代码：
```cpp
#include<bits/stdc++.h>
int n,x,y,cntl[2],cntr[2];//cntl和cntr可以存储x和y中0和1的数量
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		cntl[x]++;
		cntr[y]++;
	}
	printf("%d",std::min(cntl[0],cntl[1])+std::min(cntr[0],cntr[1]));
	return 0;
}
```

[AC记录](/record/36387871)，请放心食用！

---

## 作者：LYR_ (赞：0)

好吧，承认跟楼上大佬思路相同。

**题意：** 

**算出一列中有多少个数字/与个数比较多/的数字不一样，共有两列，输出前面计算的数字之和。**

~~语文不好，害怕表达不清楚，加上了断句~~

聪明的小朋友们会发现，其实这题是 $O(N)$的时间复杂度，所以不用存数组。

**代码：**
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
using namespace std;

int main() {
    int n;
    cin>>n;
    int s1,s2;
    s1=s2=0; //分别记录第1、2行1的个数
    rep(i,1,n) {
        int x,y;
        cin>>x>>y;
        if(x) s1++;
        if(y) s2++;
    }
    s1=min(s1,n-s1);//比较0和1那个数量少并记录
    s2=min(s2,n-s2);//同上
    cout<<s1+s2<<endl;//输出他们的和
    return 0;
}
```

---

## 作者：开始新的记忆 (赞：0)

水题……

**题目大意**（文科不好，手打翻译，见谅）

在一个很长的走廊上，左右两边的门的状态都是十分整齐的（在一边的门的状态相同），现在有一个人随意开关了一些门，使得这些门看起来十分乱。现在他想把这些门还原到整齐的状态中，请问他最少需要改变几扇门的状态才可以使得左右两边门的状态是整齐的（在一边的一扇门要
么都开要么都关，另一边的门与之相反）
第一行一个正整数n
后n行每行两个整数x，y（0<=x,y<=1）0表示关着，1表示开着，x表示左边门的状态，y表示右边门的状态
输出一个正整数表示最小改变次数

直接看代码，应该还是比较简单的
```
#include<bits/stdc++.h>
using namespace std;
int n,ans0=0,ans1=0;

int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		if(x==1)
		    ans0++;
		if(y==1)
		    ans1++;
	}
	ans0=min(ans0,n-ans0);
	ans1=min(ans1,n-ans1);
	cout<<ans0+ans1<<endl; 
	return 0;
}
```


---

