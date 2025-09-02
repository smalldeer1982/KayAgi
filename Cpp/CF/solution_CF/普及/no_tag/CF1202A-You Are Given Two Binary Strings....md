# You Are Given Two Binary Strings...

## 题目描述

给你两个二进制字符串$x$和$y$，将$y$左移$k$位，再与$x$相加，得到字符串$s_k$，最后将其反转得到$res_k$。求当$res_k$字典序最小时的$k$。

$PS:s_k = f(x) + f(y) * 2 ^ k$（$f(a)$为$a$的十进制形式）

## 样例 #1

### 输入

```
4
1010
11
10001
110
1
1
1010101010101
11110000
```

### 输出

```
1
3
0
0
```

# 题解

## 作者：Mubuky (赞：4)

#  _**CF1202A You Are Given... 题解**_ 

![](https://api.gushi.ci/all.svg)

**首先分享一下打完这场edu的感受:**

这次的edu猛一看似乎都是字符串题，但其实千差万别(！！！)。个人感觉这次题较难，或者说不合我的胃口？（其实是我太菜），但是像T1这样的\*\*题我还是可以开心的做出来的。

**题解：**

我们先来看下出题人给出的题解：

 _**Multiplying by power of 2 is "shift left" binary operation . Reverse x and y for the simplicity and look at leftmost 1 in y (let's denote its position as pos(y)).**_ 

 _**If you move it to 0 in x then you make the revk lexicographically bigger than the reverse of x. So you should move it to 1 in x too. You can choose any 1 with position ≥pos(y).**_ 

 _**Let pos(x) be the minimum position of 1 in x, such that posx≥posy. You must move pos(y) to pos(x), otherwise the 1 in posx still be present in revk and it will be not optimal.**_ 

 _**So, the solution is next: reverse x and y, find posy, find pos(x)≥pos(y), print pos(x)−pos(y).**_ 

他说了啥？？？什么pospos的？

其实，他较为准确的讲完了这道题的解决方案，让我再来用中文说一遍（思路有略微区别）：

首先,我们都知道**乘以2的幂就是二进制左移运算**，也就是说题目中的y\*2^k其实是把**二进制串y左移k位**，空位补0。这样那串式子就只剩下了x+y。

求x+y翻转后的字典序最小：我们知道翻转后字典序最小可以转化为翻转前从前往后看字典序最小（..其实是一模一样的），再结合二进制加法1+1=0的性质，尽力把二进制串y最靠右的"1"通过加法变成"0"。

如：y=1 _**1**_ 0

我们所做的就是让中间的那个最靠右的"1"（又粗又黑又歪的那个）变成"0"。

来一组完整的样例：
```cpp
1
10001
110
```
计算样例中的x+(y<<k),以下是最优方案：
```cpp
  10001(2)
+110000(2)
——————————
1000001(2)

```
即将y串"110"左移3位变成"110000"后和x串"10001"相加。

既然我们已经知道了翻转后字典序最小的串怎么找（怎么依题意操作能获得翻转后字典序最小的二进制串），那么如何用代码写出来呢？其实就是一个：

## 变版lowbit

 _**一般的**_ 

1. 在y中从右往左找到第一个"1"的位置记为pos(y);
2. 在x中以和步骤1相同的操作标记上pos(x)，但要注意此时的pos(x)必须满足pos(x)≥pos(y);
3. 输出pos(x)−pos(y).

如样例：
```cpp
1
10001
110
```
x=10001, y=110;//读入

pos(y)=2;//步骤一

pos(x)=5;//步骤二（注意满足条件pos(x)≥pos(y)，所以pos(x)不能等于1）

ans=pos(x)-pos(y)=3;//步骤三

**总结：**

比较简单的贪心思想。

**代码（本题有多种写法）：**

法1：
```cpp
#include<bits/stdc++.h>
using namespace std;

char x[100001], y[200001];
int main()
{
	int t;
	for(cin >> t; t; t -= 1){
		cin >> x >> y;
		int n = strlen(x), m = strlen(y), q = m - 1;
		while(y[q] == '0'){
			q -= 1;
		}
		q += n - m;
		int p = q;
		while(x[p] == '0'){
			p -= 1;
		}
		cout << q - p << "\n";
	}
	return 0;
}
```
法2（先翻转了二进制串，（似乎）变得更简单）：
```cpp
#include<bits/stdc++.h>
using namespace std;
char b[100001], c[200001];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s\n%s\n", b, c);
		int lenb = strlen(b),  lenc = strlen(c);
		reverse(b, b + lenb);
		reverse(c, c + lenc);
		int s = 0;
		while(c[s] == '0'){
			s++;
		}
		int s2 = s;
		while(b[s2] == '0'){
			s2++;
		}
		int j = s2 - s;
		printf("%d\n", j);
	}
}
```

 _为满足某些朋友的需求，搬运标程如下_ 

**标程：**
```
fun main(args: Array<String>) {
    val T = readLine()!!.toInt()
    for (tc in 1..T) {
        val x = readLine()!!.reversed()
        val y = readLine()!!.reversed()

        val posY = y.indexOf('1')
        val posX = x.indexOf('1', posY)
        println(posX - posY)
    }
}
```

**吐槽:** 这场edu其实还好..但是打完CodeForces就崩了是什么情况...

 _**Name:** [Educational Codeforces Round 70 (Rated for Div. 2)](https://codeforces.com/contest/1202)_ 

 _**Start:** Aug/07/2019 14:35UTC_ 

 _**Length** 02:00_ 

##  _**By Mubuky**_ 


---

## 作者：nofind (赞：0)

题意:https://www.luogu.org/problem/CF1202A

思维好题

考虑将y左移k位代表什么:就是在y后面添加k个0

既然最后要反过来,那么就要让$x+(y<<k)$的最后几位尽量为0

假设y的lowbit为z,那么y的第z-1位向右都为0,所以$x+(y<<k)$的后z-1位都只受x的限制,x的这一位是多少,它就是多少

假设x的z位为1,那么不用移动y就已经是最优解了,否则要将y的lowbit移动到x的第二个lowbit,让它们相加进位变为0

如图:
![](https://cdn.luogu.com.cn/upload/image_hosting/kr7z06qe.png)
code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int T;
char s1[maxn],s2[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",s1+1,s2+1);	
		int n=strlen(s1+1),m=strlen(s2+1);
		int num=0,ans=0;
		for(int i=m;i;i--)
			if(s2[i]=='0')num++;
			else break;
		for(int i=n-num;i;i--)
			if(s1[i]=='0')ans++;
			else break;
		printf("%d\n",ans);
	}	
	return 0;
}
```


---

## 作者：tzc_wk (赞：0)

## 一道思维题

这道题可谓是在Div.2A里算一道很难的题了，我想了足足$10$分钟才想出正解。

### 题意：
有两个01字符串$a$和$b$，如果把每个字符串看作一个二进制数的话，都会对应一个十进制数。字符串$s$对应的十进制数记作$f(s)$。你要求出满足要求的非负整数$k$，使得$f(a)+2^k*f(b)$转化为二进制后反序的字典序尽可能小。题目包含多测。

### 思路：
首先，我们知道，乘$2$的$k$次方其实就是在二进制数后面添$k$个$0$，而如果要让反序的字典序尽可能小，那么最后一位就要尽可能小，在满足这个的前提下，倒数第二位也要尽可能小，以此类推。
我们假设$b$的后$x$位全部都是$0$，而从右往左数第$x$位为$1$。那么$k$不论取什么值，$f(a)+2^k*f(b)$的后$x$位永远不会发生改变，永远与$a$的后$x$位相同。此时，如果第$a$的第$x$位为$1$，那么我们就不用添$0$了，已经取到了最优解。而如果如果第$a$的第$x$位为$0$，那么$f(a)+2^k*f(b)$的第$x$位为$1$，不是我们想要的。此时我们就要在$b$的后面添上一个$0$，然后重复上述操作。

简单来说，假设$b$最右边一个$1$是从右往左数第$x$位，那么本题要求的答案就是$a$从右往左数第$x$位左边有多少个连续的$0$。

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
string s,t;
int main(){
	cin>>T;
	while(T--){
		cin>>s>>t;
		int x=-1;
		for(int i=t.size()-1,cnt=0;i>=0;i--,cnt++){//找x
			if(t[i]=='1'){
				x=cnt;
				break;
			}
		}
		if(x==-1){
			cout<<0<<endl;
			continue;
		}
		int ans=0;
		for(int i=s.size()-x-1;i>=0;i--){//找a的从右往左数第x位左边有多少个连续的0
			if(s[i]=='0')	ans++;
			else			break;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
~~我应该讲得很详细了吧，愿管理员大人不要打回来。~~

---

## 作者：Luban (赞：0)

额，这道题居然是我比赛时唯一做出来的题，T-B想了一个小时，到凌晨困得要死，只好放弃了QAQ

言归正传，这题重难点在于想出算法

1.2^k(不会LaTeX，见谅）在二进制下一定是1后面k个‘0’，因为我们只能在第二个数后面乘上2^k，就相当于在第二个数后面添加上k个‘0’

2.因为结果是逆序旋转后的，我们要让这两数之和的末尾的‘0’尽可能多，于是我们找第二个数最后一个‘1’，和第一个数末尾对齐后，看它所对的是第一个数的第几位，记录下来

3.我们找到在记录下的位置前面的第一个‘1’，争取把它们两个凑到同一位上。因为总长度<=10^5,所以肯定不会TLE

说了这么多，上代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int main()
{
	int t,i,j;
	cin>>t;
	while(t--)
	{
		cin>>s1>>s2;
		int l1=s1.length(),l2=s2.length(),k=0;
		i=l2-1;
		while(i>=0)
		{
			if (s2[i]=='1')
			{
				int a=i+l1-l2;
				while(a>=0)
				{
					if (s1[a]=='1') break;
					k++;
					a--;
				}
				cout<<k<<endl;
				break;
			}
			i--;
		}
	}
	return 0;
}
```


---

## 作者：Kizuna_AI (赞：0)

~~这道题是高级的CF1.5的第一题，打比赛是我想了半天~~  
由于hack尚未结束（我写题解的时候），最终有没有FST会在评论中说明

[我的博客](https://blog.likecoding.ooo)  

我的思路：

首先，他的题目要求将$x+y*2^k$ 加起来并反过来，要求求出字典序最小的那个k是多少。  
这时候，我们可以发现$(10)_2=2$，也就是每`k++`，y就在二进制中往上一位  
因为要将数字反过来并要求字典序最小，所以只需要尽量让最后几位变成0。


代码：（代码很短，但我想了半天）
```
#include<bits/stdc++.h>
using namespace std;
int t;
string x,y,temp; 
int main() {
	scanf("%d",&t);
	for(int i=1;i<=t;i++) {
		cin>>x>>y;
		int count=0,ans=0;
		for(int i=y.size()-1;i>=0;i--)
			if(y[i]=='0') count++;
			else break;
		for(int i=x.size()-count-1;i>=0;i--)
			if(x[i]=='0') ans++;
			else break; 
		printf("%d\n",ans);
	}
	return 0;
}
```

---

