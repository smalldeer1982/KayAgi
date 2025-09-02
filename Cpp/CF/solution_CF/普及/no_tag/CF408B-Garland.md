# Garland

## 题目描述

有一次，Vasya在一本杂志上读到一篇文章，内容是如何用彩纸制作美丽的手工花环。Vasya立即到店里买了N张彩纸，每张纸的面积为1平方米。
花环必须由任意面积的彩纸组成，每件纸片有确定的颜色。为了制作花环，Vasya可以任意地把他现有的彩纸剪成纸片。Vasya不必用所有的纸片来制作花环。

Vasya希望花环尽可能吸引人，因此他希望用来制作花环的M张纸的总面积尽可能大。请你计算出Vasya的花环中纸片的最大总面积。

## 说明/提示

在第一个测试样例中，Vasya可以制作一个面积为6的花环：他可以使用两张彩色B，三张（但不是四张）彩色A，并将一张彩色C切成三张（比如说剪成相等的三块）。Vasya可以利用所得的碎片制作出面积为6的花环。

在第二个测试样例中，Vasya根本不能做花环——他没有一张彩色的Z。

## 样例 #1

### 输入

```
aaabbac
aabbccac
```

### 输出

```
6
```

## 样例 #2

### 输入

```
a
z
```

### 输出

```
-1```

# 题解

## 作者：_Starlit__Sky_ (赞：5)

# 洛谷 CF408B 题解

[题目传送门](https://www.luogu.com.cn/problem/CF408B)

## 题目算法

模拟

## 题目思路

题目给出了 Vasya 需要用的纸的颜色和 Vasya 已有的纸的颜色，求他最多能利用多少张纸。

我们可以遍历所有颜色（设他需要用的纸的颜色的集合为 $a$，已有的纸的颜色的集合为 $b$，最多能利用的纸的数量为 $c$；$x$ 中某种颜色的数量为 $\operatorname{count}(x)$）：

- 如果有某种颜色在 $a$ 中出现，但是没在 $b$ 中出现，就说明有种颜色的纸他需要用到，但他没有，所以无解，输出 `-1`。

- 如果某种颜色同时在 $a$ 和 $b$ 中出现，则最多能利用这种颜色的纸的数量为 $\min(\operatorname{count}(a),\operatorname{count}(b))$。（因为最多能利用的纸的数量一定小于等于已有纸的数量，即 $c \le \operatorname{count}(b)$，又因为需要求最多能利用的纸的数量，所以要取 $c$ 的最大值 $\operatorname{count}(b)$。即当 $\operatorname{count}(a) > \operatorname{count}(b)$ 时 $c=\operatorname{count}(b)$；又因为即使有再多纸，但需要的纸的数量比已有纸的数量少，且超出需要用的纸的数量的纸不会被用到，所以只会用到需要用的纸的数量的纸，所以最多能利用的纸的数量就等于需要用的纸的数量，即当 $\operatorname{count}(a) < \operatorname{count}(b)$ 时 $c=\operatorname{count}(a)$。所以最多能利用纸的数量就等于 $\min(\operatorname{count}(a),\operatorname{count}(b))$，即 $c=\min(\operatorname{count}(a),\operatorname{count}(b))$）。

## 代码

```python
a = list(input()) # 读入 Vasya 已有的纸的颜色
b = list(input()) # 读入 Vasya 需要用到的纸的颜色
cnt = 0 # 答案（即 Vasya 的花环中纸片的最大总面积）
for i in range(97,123): # 遍历字母 'a'～'z'
    c = chr(i) # 遍历到的字母
    # 如果 Vasya 需要用到某一种颜色的纸，但是他没有这种颜色的纸，就说明他不能做出他想要的花环
    if b.count(c) and not a.count(c):
        print(-1)
        break
    # 如果他有对应颜色的纸，就取他已有的纸的颜色和需要用到的纸的颜色的最小值
    cnt += min(a.count(c), b.count(c))
print(cnt) # 输出答案
```


---

## 作者：_5t0_0r2_ (赞：4)

# 简化题意

给两个字符串 $N,M$ 如果 $N$ 中有 $M$ 没有的字母，输出 -1 , 否则把它们看作两个有重集，求它们交集的元素个数。
# 分析
python 中有个叫 count 的函数，可以直接统计一个列表（包括字符串）中一个元素的个数。

存好两个字符串 26 个字母的个数后，再判别每轮的情况。

如果 a 中有任意一个 b 没有的元素，输出 -1。

否则将答案加上 a 能满足 b 的最大要求 ($\min(a,b)$)

---

## 作者：66xyyd (赞：2)

## 题意

给出两个字符串 $n,m$，如果 $m$ 中有 $n$ 中没有的字符，输出 $-1$，否则输出各字符在两字符串数量中最少数量之和。（即求交集元素数）

## 题解

首先开两个数组 $ch_n,ch_m$ 记录字符串中对应字母的数量，然后设一个答案变量 $ans$，遍历数组。如果 $ch_{m,i}$ 不为 $0$（有字符）但 $ch_{n,i}$ 为 $0$（没有字符），说明 $m$ 中有 $n$ 中没有的字符，输出 $-1$ 并返回；否则要么 $m$ 没有该字符（不用更新），要么 $m$ 有该字符，$n$ 也有该字符（取 $ch_n,ch_m$ 中的最小值）。因此 $ans$ 加上 $\min(ch_n,ch_m)$ 即可。

```cpp
#include<iostream>//for cin,cout
#include<string>//for string 
using namespace std;
int chn[30]={},chm[30];//分别存字符串n第i个英文字母的数量和字符串m第i个英文字母的数量
int main(){
	string n,m;
	cin >> n >> m;
	for(int i=0,siz=n.length();i<siz;i++){
		chn[n[i]-'a']++;
	}
	for(int i=0,siz=m.length();i<siz;i++){
		chm[m[i]-'a']++;
	}
	int ans=0;
	for(int i=0;i<26;i++){
		if(chm[i]>0 && chn[i]==0){//m里有，但是n上没有，输出-1
			cout << "-1";
			return 0;
		} else{//否则情况正常，统计最小值即可
			ans+=min(chm[i],chn[i]);
		}
	}
	cout << ans;
	return 0;
}

```

## 补充

至于题面中“为了制作花环，Vasya 可以任意地把他现有的彩纸剪成纸片。Vasya 不必用所有的纸片来制作花环。”在题意中被解释为“输出各字符在两字符串数量中最少数量之和”，作者在此进行解释。因为考虑如果 $ch_m<ch_n$，那么 Vasya 可以只使用 $ch_m$ 块彩纸参与制作；否则 Vasya 可以把 $ch_n$ 中的任意一块彩纸撕成 $ch_m$ 块彩纸，所以 Vasya 需要的任意一种颜色的彩纸要么无法满足，要么只需要 $\min(ch_n,ch_m)$ 块。

---

## 作者：天野星河 (赞：2)

## 简化题意

给定两个字符串 $N$，$M$，如果 $M$ 中有 $N$ 没有的字母，则无解（输出 $-1$）。

否则将其看成两个可重集，求两者交集的元素个数。

## 分析

开桶 $a$，$b$，分别记录 $N$，$M$ 里每个字母出现的个数，然后遍历每个字母：

- $b[i]=0$ 跳过本次循环。
- $a[i]=0$ 并且 $b[i]>0$，直接输出无解（$-1$）。
- 其他情况，将答案增加 $\min(a[i],b[i])$。

可以发现，第一条和第三条可以合并，因此操作如下：

- $a[i]=0$ 并且 $b[i]>0$，直接输出无解（$-1$）。
- 其他情况，将答案增加 $\min(a[i],b[i])$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string n, m;
	cin >> n >> m;
	map<char, int>a, b;
	for (int i = 0; i < n.size(); i++)a[n[i]]++;
	for (int i = 0; i < m.size(); i++)b[m[i]]++;
	int ans = 0;
	for (int i = 'a'; i <= 'z'; i++) {
		if (!a[i] && b[i]) {
			puts("-1");
			return 0;
		}
		ans += min(a[i], b[i]);
	}
	printf("%d", ans);
}
```

---

## 作者：KXY_Moon (赞：1)

## 概括式题意

给定两个字符串 $S,K$。

 - 如果 $S$ 包含有 $K$ 没有包含的字符，输出 ```-1```。

 - 否则就输出每个字符在 $S,K$ 的数量中最少数量的和。

## 解法
字符串模拟题。

设 $Sl$ 表示各个字符在 $S$ 中出现的次数。

设 $Kl$ 表示各个字符在 $K$ 中出现的次数。

设 $Ans$ 为答案，有：
 - 若 $Kl_i=0,Sl_i\neq0$，输出 ```-1```。
 - 否则 $Ans=\min(Sl_i,Kl_i)$。

## 代码


```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define End return
const int N = 305;
string S, K;
int Slen[N], Klen[N], Ans;
int main() {
	//freopen("Garland.in","r",stdin);
	//freopen("Garland.out","w",stdout);
	cin >> S >> K;
	for (int i = 0; i < S.size(); i++) ++Slen[S[i]];
	for (int i = 0; i < K.size(); i++) ++Klen[K[i]];
	for (int i = 'a'; i <= 'z'; i++) {
		if (Klen[i] && !Slen[i]) {
			cout << -1; End 0;
		} else Ans += min(Slen[i], Klen[i]);
	} printf("%d", Ans);
	End 0;
}
```
End.

---

## 作者：Fuxh_18 (赞：1)

## 题目大意
有两个由小写字母组成的字符串 $N$ 和 $M$，如果 $M$ 中有的字母 $N$ 中没有，就输出 ```-1```；否则输出每个字母在 $N$ 和 $M$ 的数量中最少数量的和。
## 思路
我们可以把每一个字母分别在两个字符串中的数量存起来，类似于桶排序。

**存储代码**

```cpp
int ln=n.size(),lm=m.size();
for(int i=0;i<ln;i++){
	a[n[i]]++;
}
for(int i=0;i<lm;i++){
	b[m[i]]++;
}
```



再枚举每一个字母，答案就出来啦。
## 完整代码
[已 AC，放心食用](https://www.luogu.com.cn/record/167056465)。
```cpp
#include<bits/stdc++.h>
using namespace std;
string n,m;
int a[200],b[200],ans; //存 N 中的字母，M 中的字母与答案 
int main(){
	cin>>n>>m;
	int ln=n.size(),lm=m.size();
	for(int i=0;i<ln;i++){
		a[n[i]]++;
	}
	for(int i=0;i<lm;i++){
		b[m[i]]++;
	} //存储 
	for(int i='a';i<='z';i++){
		if(b[i]&&!a[i]){ //如果 M 中有 N 中没有，就不用再搜了，输出 -1，直接结束 
			cout<<-1;
			return 0;
		}
		else{
			ans+=min(a[i],b[i]);
		}
	}
	cout<<ans;
	return 0;
}
```
一道黄题就解决了。

---

## 作者：xujiadashaoye (赞：1)

这道题可以用 $\operatorname{map}$ 来写。可以定义两个  $\operatorname{map}:a,b$ ，用 $a$ 去存储 $\operatorname{Vasya}$ 所拥有 的彩纸字符串中 $a,b,c,...,z$ 的个数，用 $b$ 去存储$\operatorname{Vasya}$ 希望的花环字符串中 $a,b,c,...,z$ 的个数。     
然后可以判断每一轮中出现的情况：    
- $b[n]=0$：跳过这一轮循环。
- $b[n]>0$ 并且 $a[n]=0$ ：直接输出 $-1$ 。   
- 剩下将迭代器增加 $\min(a[n],b[n])$ 。

但实际上还能简化。     
因为 $b[n]=0$ 其实增加的就是 $0$ 也就是 $\min(a[n],b[n])$ ，所以可以将第一条和第二条合并。也就是：  
- $a[n]==0$ 并且 $b[n]>0$输出 $-1$ 。
- 剩下将迭代器增加 $\min(a[n],b[n])$ 。 

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string n,m;cin>>n>>m;
	map<char,int>a,b;
	for(int i=0;i<n.size();i++)a[n[i]]++;
	for(int i=0;i<m.size();i++)b[m[i]]++;
	int ans=0;
	for(char i='a';i<='z';i++){
		if(a[i]==0 and b[i]>0){
			cout<<-1;
			return 0;
		}
		ans+=min(a[i],b[i]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：京润 (赞：1)

## 先简要说一下思路：
定义两个字符数组$ s[i],t[i];$
$s[i]$表示拥有的彩纸，$ t[i] $表示需要的花环。
读入后，分别用两个数组记录下每个字符串中$a……z $的个数 ，
然后$for $（$1-->26$）循环判断，
对于 $ t[i] $中的每一种字符，若 $ s[i] $中此种字符数量大于 $ t[i] $中的，则$ans+=$( $ t[i] $中此种字符数量)，否则$ans+=$( $ s[i] $中此种字符数量);

## 【注意】
1.不符合条件的情况：
 $ t[i] $中有此种字符，而$s[i]$中没有；

2.判断过程中，如果 $ t[i] $中本没有该字符，可直接跳过（详见代码）

$ Code :$
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[1010],t[1010];
int ss[30],tt[30],ans=0;
//ss储存s中字符个数，tt储存t中字符个数；
bool ok=1;
int main()
{
    scanf("%s%s",s,t);
    int sl=strlen(s);
    int tl=strlen(t);
    for(int i=0;i<sl;i++) 
	ss[s[i]-'a'+1]++;
    for(int i=0;i<tl;i++) 
	tt[t[i]-'a'+1]++;
    for(int i=1;i<=26;i++) //循环判断
	{
        if(!tt[i]) continue;
        if(!ss[i]&&tt[i]) ok=0;
        if(ss[i]>tt[i]) ans+=tt[i];
        else ans+=ss[i];
    }
    if(ok==1) printf("%d\n",ans);
	else printf("-1\n");
    return 0;
}
```


---

## 作者：Aveiro7 (赞：0)

## 题意

给两个字符串 $N$ 和 $M$，如果 $M$ 中有 $N$ 没有的字母，输出 $-1$，否则求它们的交集元素数。

## 思路

用两个数组分别记录 $N$ 字符串中的字母出现的次数，把这个数组记作 $c_n$，和 $M$ 字符串中的字母出现的次数，记为 $c_m$。如果 $c_m$ 的第 $i$ 项不为零，且 $c_n$ 的第 $i$ 项为零，则说明 $M$ 中有 $N$ 没有的字母，输出 $-1$ 即可。反之将 $ans$ 增加 $c_n$ 的第 $i$ 项与 $c_m$ 的第 $i$ 项的最小值即可。

## Code:

```cpp

#include<bits/stdc++.h>
using namespace std;
int cn[27],cm[27],i,len,ans;//用两个数组分别记录N字符串中的字母出现的次数和M字符串中的字母出现的次数
int main(){
	string N,M;
	cin>>N>>M;
    len=N.size();
	for(i=0;i<len;i++){
		cn[N[i]-'a']++;
	}
    len=M.size();
	for(i=0;i<len;i++){
		cm[M[i]-'a']++;
	}
	for(i=0;i<26;i++){
		if(cm[i]>0 && cn[i]==0){//M里有，但是N上没有，输出-1
			cout << "-1";
			return 0;
		} else{//否则情况正常，统计最小值即可
			ans+=min(cm[i],cn[i]);
		}
	}
	cout << ans;//输出 
	return 0;
}
```

## 另外

**感谢管理员大大的耐心审核！**


---

## 作者：nj_peak (赞：0)

# 题目大意
给定两个字符串 $a$ 和 $b$ ，如果 $a$ 和 $b$ 中没有字符，你就输出 $-1$，否则就输出各字符在两字符串数量中最少数量之和。
## 答题思路
首先使用两个数组 $k[1005]$ 和 $p[1005]$ 用于储存字符串，然后遍历整个数组。

总结来说就是当 $k[i]=0$ 和 $p[i]>0$ 输出 $-1$ ，否则将答案加上 $k[i]$ 和 $p[i]$ 的最小值，最后输出结果。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k[1005]={},p[1005]={},sum=0;//这步很重要，一定要初始化两个数组和sum！！！ 
								//当面对多测试点时，sum=0现的尤其重要！！！ 
								//另外，数组设大一点不会"爆炸"哟~ (＾Ｕ＾)ノ~ＹＯ 
string a,b;//注意了，一定是string类型，不是char类型哟~ 
int la,lb,j;
int main()
{ 
	cin>>a>>b;//string类型的不能用scanf和printf。 
	la=a.size();//a.size()表示a的长度，也可以写成a.length()。 
	lb=b.size();
	for(int i=0,j=la;i<j;i++)
	{
		k[a[i]-'a']++;
	}
	for(int i=0,j=lb;i<j;i++)
	{
		p[b[i]-'a']++;
	}
	for(int i=0;i<26;i++)
	{
		if(p[i]>0 && k[i]==0)
		{
			printf("-1");//输出-1 
			return 0;
		} 
		else
		{
			sum=sum+min(p[i],k[i]);
		}
	}
	printf("%d",sum);//输出 sum。
	return 0;
}
```

---

