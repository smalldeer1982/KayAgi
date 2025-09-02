# Roman Roulette

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=66

[PDF](https://uva.onlinejudge.org/external/1/p130.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/caee382d0a44b73c133d86736efebb87c565fd81.png)

## 样例 #1

### 输入

```
5 2
1 5
0 0```

### 输出

```
3
1```

# 题解

## 作者：__UrFnr__ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/UVA130)

**题目大意**：有 $n$ 个人，按顺时针方向从 $1$ 开始数到第 $k$ 个人，报到 $k$ 的人离开。接着数到第 $k$ 个的人站在离开的人的位置上。然后从离开者的后继位置开始数，重复此过程直到只剩下 $1$ 个人。

**题目思路**：这道题是约瑟夫问题的一个另型，也是通过利用约瑟夫环来做的，我们可以通过约瑟夫问题的做法加上题意的模拟即可做出本题。

由于思路过于清晰，代码就不贴了，相信你们都懂。

---

## 作者：ISTP (赞：4)

## 引子

这是蒟蒻柒米的第一篇题解，请多关照。

做完觉得有点绕，毕竟是道约瑟夫环变形。逛了一圈题解发现没有人细讲......虽然是道基础的模拟，也值得一篇细致的题解。

~~因为它很烦，柒米花了近一小时来调。~~

不了解约瑟夫问题的话可以先做下 [ P1996 - 约瑟夫问题 ](https://www.luogu.com.cn/problem/P1996)。

## 题面

[原题面：https://www.luogu.com.cn/problem/UVA130](https://www.luogu.com.cn/problem/UVA130)

这里放个核心题目描述：

$ N $ 个人排成一圈，按顺时针从 1 到 $ N $ 编号。从 1 开始顺时针数到第 $ k $ 个人，让其出圈，接着**再往后数到第 $ k $ 个人，让他站在出圈者的位置上。**然后**从先前出圈者的后继位置开始数**，重复上述过程直到圈中只剩 1 个人。当 $ N $ = 5， $ k $ = 2时，出圈者的顺序为：2，5，3，1，即最后留下4。**现求从第几个人开始数能使最后留下的是第 1 人。**

重要的地方，也就是与经典约瑟夫环不一样的地方，或者说可能的坑点，已经标粗了。

## 输入

先处理一下输入。

这是道多组数据。终止条件在原版的英文题面里有提及，**当 $ N $ 和 $ k $ 都为 0 时终止输入。**

下面是柒米的输入：

```cpp
cin >> n >> k;
while(n && k){
    //这里是一堆代码
    cin >> n >> k;
}
```

不过逛题解时发现 [白いバラの夜](https://www.luogu.com.cn/user/125109) 的输入更简洁一些（借鉴ing）。

```cpp
while(cin >> n >> k && n && k){
    //这里是一堆代码
}
```

## 模拟

接下来就是最核心的**模拟**求解。

考虑到它的数据范围很小，10 ^ 2，完全可以模拟跑一遍。

讲解在注释里，和代码配合食用。

```cpp
for(int i = 1; i <= n; i ++) f[i] = i; //初始化，所有人按位置站圈
int pos = 1; //以 1 作为起始数
for(int i = 1; i < n; i ++){
    pos = find_nxt(pos); //找到 pos 后未出圈的第 k 个数
    f[pos] = 0; //第 k 个数出圈
    int nxt = find_nxt(pos + 1); //找到要与出圈者交换位置的数
    swap(f[pos], f[nxt]);
    pos = (pos + 1 > n) ? (1) : (pos + 1); //换完移至后继位置
}

int find_nxt(int x){ //专门封装了一个函数，用来找某数后的第 k 个数
	int cnt = k;
	while(cnt){ //其实就是数 k 次有人的位置，到了 k 次就跳出
		cnt = (f[x]) ? (cnt - 1) : (cnt); //若该位有人则计上
		if(!cnt) break; //计满就跳出，这样循环外的 x 就是要找的第 k 个数
		x = (x + 1 > n) ? (1) : (x + 1); //后移
	}
	return x;
}
```

模拟跑一遍后得到将 1 作为起始数（其实随便哪个数都可以，你爱咋咋地）时最后剩下来的数字。

## 求解

然鹅题目要求的是最后剩下数字 1 时的起始数。

呃，问题不大。

如果留下的是 1 ，那正好，直接输出我们的起始数，**即一开始 pos 的值**（按我的代码，也就是 1 ）。

留下的不是 1 的话，**就把留下的数转回 1 ，起始数也跟着转回去。**

比如样例 $ N $ = 5， $ k $ = 2 ，想象一下，1 至 5 顺时针排成一圈。模拟可知最后留下的数是 4 ，那么将结果数 4 顺时针转到 1， 转了两个数。再将起始数也转两个数，从 1 转到 3 。

再上代码：

```cpp
pos = find_nxt(pos); //找到最后剩下的那个数
cout << ((n + 2 - f[pos] > n) ? (1) : (n + 2 - f[pos])) << endl; //转圈公式。其中 (n + 2 - f[pos]) 是由 (n + 1 - (f[pos] - 1)) 得来的
```

## 完整代码

功能都已经逐步实现了，只要将正确的代码块们组合起来就可以啦。

```cpp
#include <bits/stdc++.h> // UVA130 - Roman Roulette # by_QiMi
using namespace std;
int n, k, f[101];
int find_nxt(int);
int main(){
	cin >> n >> k;
	while(n && k){
		for(int i = 1; i <= n; i ++) f[i] = i;
		int pos = 1;
		for(int i = 1; i < n; i ++){
			pos = find_nxt(pos);
			f[pos] = 0;
			int nxt = find_nxt(pos + 1);
			swap(f[pos], f[nxt]);
			pos = (pos + 1 > n) ? (1) : (pos + 1);
		}
		pos = find_nxt(pos);
		cout << ((n + 2 - f[pos] > n) ? (1) : (n + 2 - f[pos])) << endl;
		cin >> n >> k;
	}
	return 0;
}
int find_nxt(int x){
	int cnt = k;
	while(cnt){
		cnt = (f[x]) ? (cnt - 1) : (cnt);
		if(!cnt) break;
		x = (x + 1 > n) ? (1) : (x + 1);
	}
	return x;
}
```
## Ending

完结撒花！！

有问题或 hack 之类的要艾特柒米哦，也欢迎在评论区指出或私信我。

*22.12.25* 

---

## 作者：player_1_Z (赞：3)

### 先来理解题目
简单的约瑟夫问题和多组数据。

### 思路
首先想到暴力枚举每一个位置出发最后留下谁，如果是 $1$ 号，就退出并输出位置。但我们可以尝试优化。于是我们可以以第一个位置为初始位置开始模拟，然后就知道了哪一个位置可以存活，于是把初始位置在位置一的 $1$ 号移到这个位置，但是因为这个位置是在第一个位置为初始位置的情况下才能存活。所以此时从在位置 $1$ 的人开始报数就行了。如果没懂，图如下。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/855n3frl.png?x-oss-process=image/resize,m_lfit,h_200,w_300)

有图辅助理解，代码就不粘贴了，相信你们都懂。

---

## 作者：herezz (赞：2)

其实就是约瑟夫问题。

~~先把[这里](https://www.luogu.com.cn/problem/P1996)的代码复制过来~~

我们计算从 $1$ 开始报数的话最后一个出局的编号（也可以是保留的一个人的编号）与 $N+1$ （或者 $1$ ）的偏移量。所有人移动这个偏移量个单位长度，存活者编号自然会变成 $1$，第一个报数人的编号就是偏移量 $+1$，即输出的答案。

代码就不粘贴了，相信你们都懂。

---

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/UVA130)

求管理员通过 QwQ。

## 关于题目

**注意输入**：有多组数据，当 $n=0 \operatorname{and} m=0$ 时，结束输入。

## 思路

### 约瑟夫问题（跟本题没有太大关系，不想看的可以直接略过）
看到这题第一眼肯定是**暴力模拟**，但对于这种类似的题型，它们有一种称呼，叫**约瑟夫问题**。

**约瑟夫问题**：$n$ 个人标号 $1,2,\cdots, n$。顺时针站一圈，从 $1$ 号开始，每一次从当前的人顺时针数 $m$ 个，然后让这个人出局。问最后剩下的人是谁。

详见 [P1996 - 约瑟夫问题 ](https://www.luogu.com.cn/problem/P1996)。

这里展示代码，具体内容不再赘述：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x=0;
bool f[205];
int main(){
    cin>>n>>m;
    for(int k=1;k<=n;k++){//总共要出队n次
    	for(int i=1;i<=m;i++){
    		x++;
			if(x>n) x=1;
			if(f[x]) i--;//如果已出队，不能计数 
		}
		f[x]=1;//记录已出队
		cout<<x<<" ";
	}
    return 0;
}
```
### 约瑟夫问题变形

**你可以不用在乎此问题的名称**。

只看这道题目，发现数据范围过小：$n,m \le 100$，代表我们可以使用 $O(n^3)$ 的时间复杂度**直接模拟**通过此题。

我们枚举从第 $k(1 \le k \le n)$ 个人开始报数，循环内部则对此进行暴力求值。

因为过于简单，直接展示代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x=0,a[105],f[105];
int main(){
    while(cin>>n>>m){
    	if(n==0&&m==0) return 0;
    	for(int k=1;k<=n;k++){
    		bool c=0;
    		x=k-1;
    		f[0]=1;
    		for(int i=1;i<=105;i++) a[i]=i,f[i]=0;
	    	for(int i=1;i<n;i++){
		    	for(int j=1;j<=m;j++){
		    		x++;
					if(x>n) x=1;
					if(f[a[x]]) j--;
				}
				f[a[x]]=1;
				if(a[x]==1){
					c=1;
					break;
				}
				int y=x;
				for(int j=1;j<=m;j++){
		    		x++;
					if(x>n) x=1;
					if(f[a[x]]) j--;
				}
				a[y]=a[x];
				a[x]=0;
				x=y;
			}
			if(!c){
				cout<<k<<"\n";
				break;
			}
		}
	}
    return 0;
}
```

其中，$a[i]$ 表示第 $i$ 个位置上的人，$f[j]$ 表示第 $j$ 个人有没有被出圈。

---

## 作者：_qumingnan_ (赞：1)

[题目跳楼机](https://www.luogu.com.cn/problem/UVA130)
# 正文开始

## 阅读理解
这道题其实很好理解，就是[约瑟夫问题](https://www.luogu.com.cn/problem/P1996)，然后求从第几个开始数可以让第 $1$ 个人是最晚出圈的。

## 思路一：直接暴力
既然是约瑟夫问题的变种，那肯定就直接照搬约瑟夫问题的代码呀。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;//人数；报数；当前人位置 
bool f[205];
int main(){
    cin>>n>>m;
    for(int k=1;k<=n;k++){
    	for(int i=1;i<=m;i++){
    		x=(x%n)+1;//让 x 保持在 1~n 之间 
			if(f[x])i--;//第 x 号人已经出圈，这样一次数的不算 
		}
		f[x]=1;//做个标记 
		cout<<x<<' ';
	}
    return 0;
}
```
由于 $N,M\le100$，所以，可以直接在原代码上改暴力。

那在这个代码的基础上怎么改呢？首先先改一下输入：
```cpp
whle(cin>>n>>m){}
```
接着，我们需要暴力枚举从第 $i$ 个开始的情况，于是我们要在外面加一层循环，再让 $x$ 从 $i$ 开始。
```cpp
for(int j=0;j<n;j++){
	x=j;
}
```
然后我们发现，他需要输出最后一个出圈的为 $1$ 的情况，不需要输出出圈情况。我们可以用一个 $a$ 数组来统计出圈情况，再用一个 $b$ 数组来处理人换位置的情况。最后如果 $a_n=1$，就输出就行了。

最后，别忘了清空标记和重置 $b$ 数组。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,a[205],b[205],i,j,k;
bool f[205];
int main(){
    while(cin>>n>>m){
    	if(n==0&&m==0)break;
    	for(j=0;j<n;j++){
			for(i=1;i<=n;i++)f[i]=0,b[i]=i;
    		x=j;
			for(k=1;k<=n;k++){
				for(i=1;i<=m;i++){
		    		x=(x%n)+1;
					if(f[b[x]])i--;
				}
				a[k]=b[x];
				int c=x;
				for(i=1;i<=m;i++){
		    		c=(c%n)+1;
					if(f[b[c]])i--;
				}
				swap(b[x],b[c]);//换位 
				f[b[c]]=1;
			}
			if(a[n]==1){cout<<j+1<<"\n";break;}//因为 j 从 0 开始，所以要 +1
		}
	}
	return 0;
}
```

## 思路二：找规律
我们手动枚举 ~~（我不会告诉你我是代码枚举的）~~ 一下样例，便能得到以下结果：


||第 $1$ 个出圈的人|第 $2$ 个出圈的人|第 $3$ 个出圈的人|第 $4$ 个出圈的人|第 $5$ 个出圈的人|
|:-:|:-:|:-:|:-:|:-:|:-:|
|从 $1$ 开始数|$2$|$5$|$3$|$1$|$4$|
|从 $2$ 开始数|$3$|$1$|$4$|$2$|$5$|
|从 $3$ 开始数|$4$|$2$|$5$|$3$|$1$|
|从 $4$ 开始数|$5$|$3$|$1$|$4$|$2$|
|从 $5$ 开始数|$1$|$4$|$2$|$5$|$3$|

我们依次看每列，发现对于第 $i(i\ge 2)$ 个数是等于第 $i-1$ 个数 $+1$ 的然后当第 $i$ 个数大于 $n$ 时，就会变成 $1$，多枚举几个样例，我们便能发现确实是这样。于是我们便可以只求从 $1$ 开始数的最后一位是什么，然后再使用一个公式：

- $ans=(n+1)-i+1$

其中，$i$ 为从 $1$ 开始数的最后一个出圈的人。

### 代码实现
直接套用公式就好了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,a[205],b[205],i,j,k;
bool f[205];
int main(){
    while(cin>>n>>m){
    	if(n==0&&m==0)break;
		for(i=1;i<=n;i++)f[i]=0,b[i]=i;
    	bool d=1;
		for(k=1;k<=n;k++){
			for(i=1;i<=m;i++){
		   		x=(x%n)+1;
				if(f[b[x]])i--;
			}
			f[b[x]]=1;
			a[k]=b[x];
			int c=x,s=0;
			for(i=1;i<=m&&s<n;i++){
			c=(c%n)+1;
			if(f[b[c]])i--,s++;
			else s=0; 
			}
			swap(b[x],b[c]); //换位 
		}
		if(a[n]==1)cout<<"1\n";//记得特判
		else cout<<(n+1)-a[n]+1<<'\n';
	}
	return 0;
}
```

---

## 作者：NotNaLocker (赞：0)

## UVA130 Roman Roulette 题解
### 几句闲话

看见楼上大佬思路如此详尽，本来不想写了，但为了~~水咕值~~补充说明还是写了这篇题解。

### 算法种类

**模拟**，一个约瑟夫变种问题。

在做这道题之前，你得先知道什么是**约瑟夫环**。

[典型例题！](https://www.luogu.com.cn/problem/P1996)

$n$ 个人围成一圈，从第一个人开始报数,数到 $m$ 的人出列，再由下一个人重新从 $1$ 开始报数，数到 $m$ 的人再出圈，依次类推，直到所有的人都出圈，请输出依次出圈人的编号。

### 主要思路

一个 while 循环用来模拟人出圈、进圈的行动：

```cpp
while(cin>>n>>k&&n&&k){
	//代码...
}
```
#### First. 初始化

```cpp
for(int i=1;i<=n;i++) a[i]=i;  //初始化编号。
ans=1;  //最后留下的人的编号，初始化为1。便于当不满足条件时直接输出。
```
#### Second. 模拟核心代码

```cpp
for(int i=1;i<n;i++){  //i<n是因为要把最后一次数数留下，因为最后一次不需要以下的处理。
	ans=find(ans);  //find用于找到出圈的人的编号。
	a[ans]=0;  //标记为出圈。
	swp=find(ans+1);  //接着数到第k个人。
	swap(a[swp],a[ans]);  //让他站在出圈者的位置上。
	ans=(ans+1>n) ? 1 : (ans+1);  //前进一个，从这个位置继续循环。
}
```
#### Third. 最后的处理

```cpp
ans=find(ans);  //最后一次数数。
cout<<((n+2-a[ans]>n) ? 1 : (n+2-a[ans]))<<endl;
```
当最后留下的数不是 $1$ 时，可以**顺时针**调到 $1$，**把起始位置也按顺时针移动相同的距离即可**。

#### Fourth. 函数核心代码
```cpp
int find(int x){
	int cnt=k;  //递减器。限制循环k步。
	while(cnt){
		cnt=(a[x]) ? (cnt-1) : (cnt);  //当这个人已经出圈，不计入递减。
		if(!cnt) break;  //如果这时步骤用光，立刻退出，很重要。
		x=(x+1>n) ? 1 :(x+1);  //编号环形计数。
	}
	return x;  //华丽结束
}
```
看到这里，相信~~完整代码不必放出了~~思路已经清晰了，放代码啦!
## AC coding

```cpp
#include<bits/stdc++.h>
#define f(i,j,n) for(i=j;i<=n;i++)
using namespace std;
int n,k,i,ans,swp;
int a[1005];
int find(int x){
	int cnt=k;
	while(cnt){
		cnt=(a[x]) ? (cnt-1) : (cnt);
		if(!cnt) break;
		x=(x+1>n) ? 1 :(x+1);
	}
	return x;
}
int main(){
	while(cin>>n>>k&&n&&k){
		f(i,1,n) a[i]=i;
		ans=1;
		f(i,1,n-1){
			ans=find(ans);
			a[ans]=0;
			swp=find(ans+1);
			swap(a[swp],a[ans]);
			ans=(ans+1>n) ? 1 : (ans+1);
		}
		ans=find(ans);
		cout<<((n+2-a[ans]>n) ? 1 : (n+2-a[ans]))<<endl;
	}
	return 0;
}
```
## Thanks for watching.

---

## 作者：Low_key_smile (赞：0)

这道题打眼一看就是约瑟夫问题

[题面](https://www.luogu.com.cn/problem/UVA130)

这道题的意思就是 $n$个人排成一圈，按顺时针从 $1$ 到 $n$ 编号。从 $1$ 开始顺时针数到第 $k$ 个人，让其出圈，接着数到第 $k$ 个人，让他站在出圈者的位置上。然后从出圈者的后继位置开始数，重复上述过程直到环中只剩 $1$ 个人。当 $n=5$ , $k=2$ 时，出环者的顺序为：$2$ ，$5$ ，$3$ ，$1$ ；最后留下 $4$ 。

所以就是说按照题意模拟即可，代码的话和约瑟夫问题差不多，就是多了个修改，比较简单，还是留给读者思考把

---

## 作者：XCD_OIworld_rookie (赞：0)

## 约瑟夫变形。。。 

vector打暴力，简单模拟，

循环杀人，直到只有一个幸存者。m为被杀死人的编号

计算埋葬者在数组中的位置，人数按已杀死m号人后计算

如果t在m的后面，则要加1(数组尺寸在此时并未改变)

##### 黑题？？？

code：
```cpp
//by xuchendong_2006	 编程时间： Tue Aug 06 14:56:49 2019

#include<bits/stdc++.h>
using namespace std;
vector<int> v;//能用vector解决的问题984问题 
int main()
{
    int n,k;
	for(;~scanf("%d%d",&n,&k) &&(n||k);)
    {
        v.clear();
        for(int i = 1; i <= n; i++)
             v.push_back(i);
        int m = (k-1)%v.size(),t;
		for(;v.size() > 1;)
        {
            t = (m + (k-1)) % (v.size()-1);
            if(t >= m)
                t = (t+1) % v.size();
            else
                t = t % v.size();
            v[m] = v[t];
            v.erase(v.begin()+t);
            if(t >= m)
                m = (m + k)%v.size();
            else
                m = (m + k-1)%v.size();
        }
        printf("%d\n",(n-(v.front()-1))%n+1);
    }
    return 0;
}
```


---

## 作者：koukou (赞：0)

------------

其实，这就是[约瑟夫问题](https://baike.baidu.com/item/%E7%BA%A6%E7%91%9F%E5%A4%AB%E9%97%AE%E9%A2%98/3857719?fr=ge_ala)（详见下面），加了个移位，代码小改动即可。

参考 P1996 约瑟夫问题。


------------
## 约瑟夫问题
> $n$ 个人围成一圈，从第一个人开始报数,数到 $m$ 的人出列，再由下一个人重新从 $1$ 开始报数，数到 $m$ 的人再出圈，依次类推，直到所有的人都出圈，请输出依次出圈人的编号。

一个简单的模拟题，看代码。

```
#include<iostream>//cin cout不说了
#include<cstring>//memset要用cstring库。
bool a[110];//用来记录该player是否在圈内，ture为在圈内，false为出圈。
int m,n,x=0,y=0,z=0;//x为报到第x个数，y为到第y人，z为已经z人出圈。 
using namespace std;
int main()
{
	memset(a,true,sizeof(a));//把a初始化为true，以前学pas的不要把ture和sizeof位置搞错
	cin>>n>>m;//读入
	while(z!=n)//当还有人未出圈时
	{
		y++;//人+1
		if (y==n+1) y=1;//当人数到n+1时，因为是环型，所以重新回到1.
		if (a[y]) x++;//如果这个人还在圈里就报数。
		if (x==m)//当之个人很倒霉，报到那个数字时
		{
			x=0;//把报到的数字归0。
			cout<<y<<' ';//把这个人的序号输出
			a[y]=false;//这个人出圈了
			z++;//多一个出圈的人
		}
	}
	return 0;
}
```

## 接下来，加上移位：

```cpp
#include<iostream>
using namespace std;
int n, k;
int main()
{
	cin >> n >> k;
	for(int i = 1; cin >> n >> k && n && k; i++）
  	{
		//do something
	}
	return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## 题目分析

- 直接暴力模拟，将出圈者从数组中删除再加到队列的末尾，然后再开始下一轮计数。重复这一过程直到只剩下一个人。时间复杂度为 $O(N^2)$，不适合解决规模较大的问题。

- 约瑟夫环，是一个经典问题。已知 $N$ 个人围成一圈，并且从第 1 个人开始报数，数到第 $k$ 个人后，此人出列；下一位从 1 开始报数，数到 $k$ 的人出列；依此类推，直到所有人出列。问出列顺序。

  该问题的递推公式为：

  $$ \begin{aligned} f(n,k)= \begin{cases} 0& &n=1\\ (f(n-1,k)+k)\ \bmod \ n& &n>1 \end{cases} \end{aligned}$$

  其中 $n$ 代表的是总人数，$k$ 表示报数的数字是几。

  可以依据递推公式，快速求得圆圈中最后幸存者的编号。

时间复杂度为线性。

---

## 作者：白いバラの夜 (赞：0)

题目：约瑟夫环变形，每次第k个出去后，他后面的第k个人站到他的位置，然后从这个位置继续；

            现在你的编号，是1号，问从几号开始你回剩到最后。

分析：数论，模拟。直接模拟计算即可。

            设从x位置开始则，最后剩下的人是s（编号0~n-1）有，你的新编号为m-x+1 = s，则x = m-s+1。

说明：看错题了，输出从1开始数的答案，WA了2次。

~~~cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int p[101];
int find(int s,int k,int n){
    while(k) 
        if(p[s=(s+1)%n]!=-1)
            k--;
    return s;
}
int main(){
    int n,k,m;
    while(cin>>n>>k&&n){
        m=n;
        for(int i=0;i<m;i++)
            p[i]=i;
        int s=(k-1)%n;
        for(int i=1;i<m;i++){
            p[s]=-1;
            swap(p[find(s,k,n)],p[s]);
            s=find(s, k, n);
        }
        printf("%d\n",(m-p[s])%m+1);
    }
}
~~~

---

