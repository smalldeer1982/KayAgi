# Swimming Pool

## 题目背景

**请注意，四边形 $ABCD$ 中，四个点必须*顺次*是 $A,B,C,D$**，不允许 $AB$ 是一条对角线之类的情况。

## 题目描述

小 J 想要建一个四边形游泳池 $ABCD$。他希望有一组对边互相平行（方便搞一些家庭比赛），另外一组对边不平行（否则会显得太没有个性）。换言之，**他需要让这个游泳池是个梯形**。

给出四个正整数 $p,q,r,s$，判断他能否造一个符合题意的游泳池，使得 $AB=p,BC=q,CD=r,DA=s$。


## 说明/提示

【样例解释】

第一组数据显然无法构成四边形。

第二组数据只能构成平行四边形。

第三组数据确实可以构成梯形。

【数据范围】

本题共 $6$ 个测试点，注意测试点不等分。

|测试点编号|特殊性质|分值|
|:-:|:-:|:-:|
|$1$|可构成梯形当且仅当可构成四边形|$19$|
|$2$|$p<r<s$ 且 $q<s$|$17$|
|$3$|$p,q,r,s\le 2$|$7$|
|$4$|$p<r$ 且 $q<s$|$12$|
|$5$|输入必能构成四边形|$18$|
|$6$|无特殊性质|$27$|

对于全体数据，保证 $1\le T\le 10^4$，$1\le p,q,r,s\le 5\times 10^8$，输入皆为正整数。

## 样例 #1

### 输入

```
3
20 2 4 8
3 5 3 5
1 2 4 3
```

### 输出

```
no
no
yes
```

# 题解

## 作者：yummy (赞：20)

# B. Swimming Pool 官方题解

本题涉及的主要知识点：

- 【1】几何（初中部分）
- 【2】if 语句
- （非必须）【3】绝对值函数

### Part 1 判断是否构成四边形

要想构成梯形，首先要构成四边形。根据两点间线段最短可知，四条边可以构成四边形当且仅当任意一边小于另外三边之和，即 $p<q+r+s$ 等（共有 $4$ 个条件）。

其实把四个条件都写上已经可以完成这部分任务了，但是我们有没有更优雅的写法？

还是使用线段公理，我们可以把构成四边形（或其他多边形）的条件转化为”周长大于最长边长度的两倍“。从直观上看，如果你要用一个绳圈套住长 $l$ 的边，这个绳圈长度至少要 $2l$。

求最长边长度可以使用 `max` 求出：可以使用传统的 `max(max(p,q),max(r,s))`，也可以采用当前 NOI 系列比赛已经支持的 `max({p,q,r,s})` 一次性求出四个数的最大值。

~~求和时注意数据类型，四个 $10^9$ 范围的数加起来可能会爆 `int`。~~

我怕本题 AC 率不够高，把 $10^9$ 改成 $5\times 10^8$ 了。

### Part 2 判断四边形有没有可能是梯形

![](https://cdn.luogu.com.cn/upload/image_hosting/lc8t8ez7.png)

如图，假如有梯形 $ABCD$ 且 $AB//CD$，我们看看它需要满足的性质。

过 $D$ 作 $DE//BC$ 交 $AB$ 于 $E$。则 $AE$ 为 $p-r$，$AD$ 为 $s$，$DE$ 为 $q$。在三角形 $ADE$ 中，$|p-r|>|s-q|$。类似地，如果 $AD//BC$，那么 $|s-q|>|p-r|$。

这样我们就知道，如果要构成梯形，那么必须满足**对边差不相等**。反过来，对边差不相等的时候一定可以构成梯形吗？答案是肯定的，下面我们来证明这一点。

取对边差更大的一组对边（不妨认为是 $p,r$），以 $s,q,|p-r|$ 为边构造三角形 $ADE$。然后接下来延长 $AE$ 至 $B$ 使得 $AB=\max(p,r)$，再作平行四边形 $DEBC$ 即可。

### Part 3 参考代码

C++ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long p,q,r,s;
int main(){
	for(scanf("%d",&T);T;T--){
		scanf("%lld%lld%lld%lld",&p,&q,&r,&s);
		if(2*max({p,q,r,s}) >= p+q+r+s or abs(p-r)==abs(q-s))
			puts("no");
		else puts("yes");
	}
	return 0;
}
```

Python 3 代码：

```python

for i in range(int(input())):
    p,q,r,s=map(int,input().split())
    if 2*max(p,q,r,s)>=p+q+r+s or abs(p-r)==abs(q-s):
        print("no")
    else:
        print("yes")
```

---

## 作者：Chitose_ (赞：7)

## 我的第一篇题解，如有问题请各位管理员以及oier斧正。

首先，注意到此题边是按顺序读入的，所以设四条边分别为 $a_1,a_2,a_3,a_4$，所以 $a_1$ 与 $a_3$ 肯定为对边，同理，$a_2$ 与 $a_4$ 肯定为对边。
其次，分两种情况讨论。先假设若 $a_1$ 与 $a_3$ 平行，将 $a_4$ 这条腰沿 $a_1$ 的方向平移，当且仅当 $a_2,a_4$ 与 $|a_1-a_3|$ 能够构成三角形时，即能满足 $a_1,a_2,a_3,a_4$ 能够构成梯形，示意图如下。


![梯形平移腰](https://cdn.luogu.com.cn/upload/image_hosting/uxy4hog0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

同理，再考虑 $a_2$ 与 $a_4$ 平行。\
只要以上两种情况满足一种既可证的四条边能够构成平行四边形，代码如下。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[5],tmp;
bool flag;

bool judge(int a,int b,int c){//证明a,b,c三条边能否构成三角形
	if(a+b>c && a+c>b && b+c>a) return true;
	else return false;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		flag=false;
		for(int j=1;j<=4;j++) {
			scanf("%d",&a[j]);
		} 
		tmp=abs(a[3]-a[1]);// a[1] 与 a[3] 平行
		if(judge(tmp,a[2],a[4])) flag=true;
		tmp=abs(a[2]-a[4]);// a[2] 与 a[4] 平行
		if(judge(a[1],a[3],tmp)) flag=true;
		if(flag) cout<<"yes"<<endl;//两种情况有一种成立即为真
		else cout<<"no"<<endl;
 	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# P10245 Swimming Pool

### 题意

给你四条边 $abcd$，求这四条边是否可以组成梯形。

### 思路

这显然是一道简单的普通数学题。

判断是否能构成梯形只需看四条边是否能满足,上底减下底的绝对值小于两腰之和且大于两腰之差。

#### 证明过程

![](https://cdn.luogu.com.cn/upload/image_hosting/03axmv5a.png)

如图，$AB=a$，$BC=b$，$CD=c$，$AD=d$。

过点 $D$ 作 $AB$ 的平行线交 $BC$ 于点 $E$。

若四边形 $ABCD$ 为梯形，则 $AD$ 平行于 $BE$，

又 $AB$ 平行 $DE$，

所以四边形 $ABED$ 是平行四边形，

则 $BE=AD=d$。

因为 $BC=b$，

所以 $EC=BC-BE=b-d$。

由上文知四边形 $ABED$ 是平行四边形，

则 $DE=AB=a$。

于是在三角形 $CDE$ 中。

根据三角形的三边关系可知：

$CE<DE+DC$ 并且 $CE>DC-DE$。

即 $b-a>c-d$ 并且 $b-a<c+d$。

#### 注意事项
- 因为题目中有表明，所以只有 $ac$ 和 $bd$ 是对边。
- 因为 $a-b$ 有几率出现负数，所以用绝对值函数 abs 来做。

### 代码
```
#include <bits/stdc++.h>
using namespace std;
inline int rd(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return f*s;
}
inline void print(int x){
	if(x<0){putchar('-');print(-x);return;}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
int t,a,b,c,d;
int main(){    
    t=rd();
    while(t--){
    	a=rd();b=rd();c=rd();d=rd();
    	bool f=0,k=0;
			if(a!=c&&b+d>abs(a-c)&&abs(b-d)<abs(a-c))f=1; 
			else if(b!=d&&a+c>abs(b-d)&&abs(a-c)<abs(b-d))f=1;
		if(f==1)cout<<"yes\n";
		else cout<<"no\n";
	}
    return 0; 
}
```

---

## 作者：MoonCake2011 (赞：1)

就是用[平移腰法](https://zhidao.baidu.com/question/464952805.html)证明。

上面的连接是百度百科。

注意边的顺序，所以只能搞 $p,r$  为上底下底的情况和 $q,s$ 为上底下底的情况。

所以直接就能写代码了。

~~上次月赛第一题的题解没给代码有人说我不仁慈，那还是给个代码吧！~~

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int a[4],b[4];
	cin>>a[0]>>a[1]>>a[2]>>a[3];
	if(a[2]<a[0]) swap(a[0],a[2]);
	if(a[3]<a[1]) swap(a[1],a[3]);
	b[0]=a[2]-a[0];
	b[1]=a[1],b[2]=a[3];
	sort(b,b+3);
	if(b[0]+b[1]>b[2] && a[0]!=a[2]){
		cout<<"yes\n";
		return;
	}
	b[0]=a[3]-a[1];
	b[1]=a[0],b[2]=a[2];
	sort(b,b+3);
	if(b[0]+b[1]>b[2] && a[1]!=a[3]) cout<<"yes\n";
	else cout<<"no\n";
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：ACtheQ (赞：1)

可以把一个腰平移，与另外一个腰，和下底减去上底，构成三条边，只要这三条边能够构成三角形即可。

三角形的判定就是最小的两条边的加起来大于第三边。

注意，两组对边都可作为上下底。

```c++
#include<bits/stdc++.h>
using namespace std;
bool check(int x,int y,int z)
{
	int a[5];
	a[1]=x;
	a[2]=y;
	a[3]=z;
	sort(a+1,a+4);
	return a[1]+a[2]>a[3];
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(check(abs(c-a),b,d)||check(abs(b-d),a,c)) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	} 
	return 0;
}
```

---

## 作者：Vitamin_B (赞：1)

# 前言
你说得对，但是百度 YYDS！
# 思路
首先假设 $a$ 为上底，$c$ 为下底，$b,d$ 为腰，则把四条边分别为 $a,b,c,d$ 的梯形将上底和下底减去上底，这样就会变成一个边长为 $b,(a-c),d$ 的三角形，这是只要判断 $b,(a-c),d$ 是否能构成三角形就行了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, a, b, c, d;
bool f (int a, int b, int c) {
	return a + b > c && a + c > b && b + c > a;
}
bool check (int& a, int& b, int& c, int& d) {
	return f (abs (a - c), b, d);
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> a >> b >> c >> d;
		cout << (check (a, b, c, d) || check (b, c, d, a) ? "yes\n" : "no\n");
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题意分析
这道题很数学，就是给你四条边，问你能不能组成一个梯形。
## 答题思路
能否组成一个梯形主要用了几个性质，主要是由三角形三边关系和两点间距离公式来推的，有兴趣可以自己推导一下，在这里就不废话了。

（还是废话一下，我们这里分成两种情况来讨论，第一种是 ac 边为短边，bd 边是长边，第二种是反过来，我们平移梯形的腰就可以得到下面代码中的式子，百度上会有详细的推导，这里只是简要说明）

梯形有且只有一组对边平行且不相等，我们可以沿平行的对边平移一个腰与另一腰有交点，这时形成一个三角形，底边为原梯形下底 - 上底的差，另两边为两腰长由三角形两边之和大于第三边，两边之差小于第三边得两腰和 > 两底差，两腰差。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot;
int main(){
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		int p,q,r,s;
		cin>>p>>q>>r>>s;
		if((p!=r && (q+s)>abs(p-r) && abs(q-s)<abs(r-p))||(q!=s && (p+r)>abs(q-s) && abs(r-p)<abs(q-s))){
			cout<<"yes"<<endl;
		}
		else{
			cout<<"no"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：__Cby___ (赞：0)

## 题目大意
给出四条边，问能否用这四条边**顺次**首尾相连连成梯形。  
## 解题思路
能否构成梯形的判定条件为两腰之和大于两底之差且两腰之差小于两底之差。  
注意判定上下底时，只能拿对边作上下底。我比赛时因为这个被卡了一个小时。
## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[5];
int ls[4];
int main() {
	int T;
	cin >> T;
	while (T--) {
		for (int i = 1; i <= 4; i++)cin >> a[i];
		bool y = 0;
		for (int i = 1; i <= 2&&!y; i++) {
			int j = i + 2;
			if (j > 4)j %= 4;
			int t = 0;
			for (int k = 1; k <= 4; k++) {
				if (k != i && k != j)ls[++t] = a[k];
			}
			if ((ls[1] + ls[2]) > abs(a[j] - a[i])&&
				abs(ls[1] - ls[2]) < abs(a[j] - a[i])) {
				cout << "yes" << endl;
				y = 1;
				break;
			}
		}
		if (!y)cout << "no" << endl;
	}
	return 0;
}
```

---

## 作者：b1tset (赞：0)

题意：给出 $4$ 个边的边长，判断其是否能组成梯形。

### 思路

很显然，根据梯形的性质判断即可。  
梯形的性质：两斜边之和大于两底之差，两斜边之差小于两底之差。  
由于我们不知道 $4$ 条边中哪两条是斜边，哪两条是底边，所以要做两次判断：一次假设 $p$ 和 $r$ 是一对斜边，一次假设 $q$ 和 $s$ 是一对斜边，再根据上面提到的性质进行判断即可。  
注意，题目给出的四条边的顺序是不能变的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

bool solve() // 多测用函数
{
	int a, b, c, d; // 4 条边，对应题目中的 p, q, r, s
	scanf("%d %d %d %d", &a, &b, &c, &d);
	
	if (a + c > abs(b - d) && abs(a - c) < abs(b - d)) return 1; // 假设 p 和 r 是一对斜边
	if (b + d > abs(a - c) && abs(b - d) < abs(a - c)) return 1; // 假设 q 和 s 是一对斜边
	return 0; // 不是梯形
}

int main()
{
	int T;
	scanf("%d", &T); // T 组测试
	while (T--)
	{
		if (solve()) puts("yes"); // 能组成梯形
		else puts("no"); // 不能组成梯形
	}
	return 0;
}
```

---

