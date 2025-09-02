# [GCPC 2024] Interference

## 题目描述

物理可以非常有趣！
昨天，你的老师讲解了干涉现象的原理：如果你有两列波，它们在整个波长范围内的高度会相加！
因此，如果两列波都在波峰处，合成后的波峰会更高。
同样地，如果两列波都在水面以下的波谷处，合成后的波谷会更低。
从技术上讲，波的高度被称为振幅，两波峰之间的距离被称为波长。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/vaufr6oi.png)

图 I.1：样例输入 2 中三列波的干涉效果。黑点表示合成波在各点的高度。
:::

今天，你的物理老师描述了她即将进行的一个实验的设置。
她将在一维水槽中制造驻波。
由于她对物理元素的精确控制，所有波都具有精确控制的振幅，并且只会在给定长度的区间内产生。
每列波的波长始终为 $4$，且第一个正波峰总是在区间的第一个位置。
我们只在整数点上测量波的振幅。
例如，振幅为 $2$，长度为 $9$ 的一列波可以表示为 $\texttt{2\ 0\ -2\ 0\ 2\ 0\ -2\ 0\ 2}$。
如果某个点没有波，则振幅为 $0$。
你的任务是预测在给定位置处，考虑到之前所有产生的波后，合成波的高度。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 10
! 2 7 1
? 9
? 7
? 6```

### 输出

```
0
0
1```

## 样例 #2

### 输入

```
7 10
! 2 6 1
! 3 8 2
! 5 2 3
? 6
! 5 5 4
? 8
? 9```

### 输出

```
1
0
2```

## 样例 #3

### 输入

```
6 12
! 1 7 1
! 7 3 2
? 6
? 7
? 8
? 10```

### 输出

```
0
1
0
0```

## 样例 #4

### 输入

```
6 11
! 1 6 1
? 6
! 5 7 4
? 6
! 6 3 2
? 6```

### 输出

```
0
0
2```

# 题解

## 作者：a11223344 (赞：1)

观察数据范围，$w$ 的范围较大，直接对所有位置做操作显然会超时，而 $n$ 的范围较小，可以从 $n$ 入手。

对于查询操作，我们可以直接扫描当前所有的波，如果该点在波的范围内，就将答案加上该点处该波的高度；对于波的产生，则不需要任何额外操作，直接存下来就好。时间复杂度为 $O(n^2)$。

具体实现见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,p[4005],l[4005],a[4005],t;
char c;
int main(){
	cin>>n>>w;
	while(n--){
		cin>>c>>p[t];
		if(c=='?'){
			long long s=0;
			for(int i=0;i<t;++i){
				if(p[t]>=p[i]&&p[t]<p[i]+l[i]){
					if((p[t]-p[i])%4==0)s+=a[i];
					if((p[t]-p[i])%4==2)s-=a[i];
					
				}
			}
			cout<<s<<endl;
		}
		else cin>>l[t]>>a[t],t++;
	}
	return 0;
}
```

---

## 作者：qweruiopasdfjkl (赞：1)

## [P13724 [GCPC 2024] Interference](https://www.luogu.com.cn/problem/P13724) 题解  
### 解题思路   
观察题干，易知合成波的高度等于改点上波高度的和。  

然后我们考虑使用什么方法做题。从题目中 $n$ 只有 $4000$，而 $w$ 有 $10^9$ 之大，所有我们抛弃用数组储存每点的高度而 $O(1)$ 查找加输出的方法，使用记录每组的状态再用 $O(n)$ 查找加输出，省下空间，也不超时。  

最后是怎么记录每段波对点的影响。因为每列波的波长始终为 $4$，且第一个正波峰总是在区间的**第一个位置**，所以所有波都由几个 $V$ 或几个半 $V$ 组成，有两个点要加减处理，详细内容可以看代码理解。  
### 解题代码  
#### [AC记录](https://www.luogu.com.cn/record/232905850)  
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;

char c;
ll n , w , wz , ta , s;
ll zt[4010][4];// 记录状态 zt[i][1] 表示第 i 条波的起点 zt[i][2] 表示第 i 条波的长度 zt[i][1] 表示第 i 条波的振幅

int main(){
	cin >> n >> w;
	for(int i = 1; i <= n; i++){
		cin >> c;
		if(c == '!'){
			cin >> zt[s+1][1]/*起始位置*/ >> zt[s+1][2]/*长度*/ >> zt[s+1][3]/*振幅*/;// 为 ! 记录状态 
			s++;
		}else{
			cin >> wz;
			ta = 0;// 计算高度 
			for(int i = 1; i <= s; i++){// 遍历状态 
				if(wz >= zt[i][1] && wz < zt[i][1]+zt[i][2]){// 判断是否在区间内 
					if((wz-zt[i][1])%4 == 0) ta += zt[i][3];// 判断在波的位置 
					if((wz-zt[i][1])%4 == 2) ta -= zt[i][3];
					// 0 和 2 分别在 V 的左上和下面的尖角，因为波长始终为 4 所以隔两隔波从上到下(或下到上) 
				}
			}
			cout << ta << endl; 
		}
	}
	return 0;
} 
```

---

## 作者：yytmcjs (赞：1)

# P13724 [GCPC 2024] Interference
### 题目概括
在水槽内有一些波，每列波的波长都为四，且第一个正波峰都在波的区间的第一个位置。**每个位置上的波高度会相加**。有 $n$ 次操作，每次给出两种操作其中一种：

- 当输入为 `!` 时，描述一个波的起始位置 $p$、长度 $l$ 与振幅 $a$（振幅就是波的高度）。
- 当输入为 `?` 时，给定一个点，查询在此点上的波（相加）的高度。
### 思路
注意到，水池的宽度最长可达到 $10^9$，显然，每次遍历每个点修改是不可行的，于是我们想到**记录每个波的参数**，在查询时**遍历每个波**，计算其贡献。

同时我们观察到，因为每个波峰之间的距离**都为四**，所以从波的一个波峰走向相邻的波谷时，中间只会经过**一个整点**，那便是波高度为零的时候。

所以不难得出**结论**：每个波只在其波峰与波谷时取到有价值的整点，也就是当其偏移起始位置的长度 $len \bmod 4 = 1$ 或 $len \bmod 4 = 3$ 时。
### 实现思路
1. 在每次读入波的参数时记录在一个结构体数组中。
2. 对于每次询问 $P$，遍历数组中每个波，如果 $P$ 不在当前波的范围内，跳过遍历下一个。
3. 每找到一个可行的波，计算 $P$ 对于这个波起始位置的偏移量 $len$，然后对 $4$ 取模，余 $1$ 则当前点的答案 $ans$ 加上波的波峰高度 $a$，余 $3$ 则减去，否则不变。
4. 输出答案。

顺便提一嘴，因为每个询问都保证在水池宽度以内，所以读入的水池宽度没有任何用处。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

struct wave{		//记录每个波的参数 
	int p,l;
	long long a;
}w[10005];

int n,W,tot;

int main(){
	cin >> n >> W;		//读入 
	for (int i=1;i<=n;i++){
		char op;
		cin >> op;
		if (op=='!'){		//将波的参数读入 
			int p,l;
			long long a;
			cin >> p >> l >> a;
			w[++tot].p=p;
			w[tot].l=l;
			w[tot].a=a;
		}
		else{
			int P;
			cin >> P;
			long long ans=0;
			for (int i=1;i<=tot;i++){		//遍历每个波 
				wave x=w[i];
				if (P<x.p || P>x.p+x.l-1) continue;		//不在范围内 
				int len=P-x.p+1;		//偏移量 
				if (len%4==1)		//在波峰上 
					ans+=x.a;
				else if (len%4==3)		//在波谷上 
					ans-=x.a;
			}
			cout << ans << endl;		//输出 
		}
	}
	return 0;
}

```

---

## 作者：Gilbert1206 (赞：1)

## 题解：P13724 [GCPC 2024] Interference

[题目传送门](https://www.luogu.com.cn/problem/P13724)

## 思路

不难发现，这道题 $n$ 的数据范围为 $1 \le n \le 4000$，所以给了很多的时间去直接模拟。这道题因为波长是固定为 $4$ 的，所以可以得出第一次波的高度为振幅 $a_i$，第二次为 $0$，第三次为 $-a_i$，第四次则又为 $0$。

这道题因为会有在线的去添加一个波，所以可以用一个数组去记录当前的波的条件，当需要去查询时我们需要做如下几步。

1.  判断那个波是否可以到达 $p$ 点。
2.  找到 $p$ 点在波长的位置。

最后只需要去看每一个波经过 $p$ 点此时的波高算出并求和即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct pt{
	int ap,bp,cp;
}a[23000];
signed main(){
	int n,w,t=0;
	cin>>n>>w;
	while(n--){
		char s;
		int b,c,d;
		cin>>s;
		if(s=='!'){
            //记录波的情况
			cin>>b>>c>>d;
			a[t].ap=b,a[t].bp=c,a[t].cp=d;
			t++;
		}
		else{
			cin>>b;
			int ans=0;
			for(int i=0;i<t;i++){
                //判断这条波是否到点 p。
				if(a[i].ap>b||a[i].ap+a[i].bp-1<b){
					continue;
				}
                //看在波长的哪个位置
				if((b-a[i].ap+1)%4==1){
					ans+=a[i].cp;
				}
				else if((b-a[i].ap+1)%4==3){
					ans-=a[i].cp;
				}
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}

```

---

## 作者：QQ9178 (赞：0)

### 思路：  
观察发现，每个波长都是有规律的，每四个一次循环，第一次和第三次不变，第二次减少相应的振幅，第四次增加相应的振幅，利用数组存储每个波的开始位置，长度，振幅，还用一个初始值为 $0$ 的变量记录这是第几个波。  

当然，计算最后的值时要特判：
- 不能比给定的开头短，否则不计算。
- 不能比给定的结尾（开头加长度）长，否则不计算。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
int s[4005],l[4005],k[4005],cnt;
using namespace std;
signed main() {
    int n,w;
    cin>>n>>w;
    while(n--) {
        char a;
        cin>>a;
        if(a=='!') {
            int s1,l1,k1;
            cin>>s1>>l1>>k1;
            s[cnt]=s1;
            l[cnt]=l1;
            k[cnt]=k1;
            cnt++;
        }else {
            int p,sum=0;
            cin>>p;
            for(int i=0;i<cnt;i++) {
                if(p<s[i]||p>=s[i]+l[i]) continue;
                if((p-s[i])%4==0) sum+=k[i];
                else if((p-s[i])%4==2) sum-=k[i];
            }
            cout<<sum<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13724)

### 题目分析
由于每个波的都是周期性的，且波长固定为 $4$，对于任意位置 $q$，仅当 $q$ 位于一个波的区间内（即 $p \le q \le p + l - 1$）这个波才对 $q$ 产生贡献，并且贡献值由偏移量 $d = (q - p) \bmod 4$ 的结果决定：  

- 如果 $d \equiv 0 \pmod 4$，贡献为 $a$（波峰）。
- 如果 $d \equiv 2 \pmod 4$，贡献为 $-a$（波谷）。
- 否则，贡献为 0。

我们只需要遍历所有已添加的波，检查位置是否在波的区间内，然后根据偏移量计算贡献并累加即可。

### 代码实现
```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6+10, M = 1e8 + 10;

int n,w;

struct node{
	int p,l,a;// 起始位置，长度，振幅
}f[N];

signed main()
{
	fst
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='!'){
			cin>>f[i].p>>f[i].l>>f[i].a;
		}
		else{
			int q,ans=0;
			cin>>q;
			for(int i=1;i<=n;i++){
				if(q<f[i].p||q>f[i].p+f[i].l-1)continue;// 不在范围内
                int d=q-f[i].p;// 偏移量
                if(d%4==0){
                    ans+=f[i].a;// 波峰
                }
                else if(d%4==2){
                    ans-=f[i].a;// 波谷
                }
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

因为 $n$ 比较小，所以每次询问的时候枚举之前加进来的每一个波，由于波长总是 $4$，所以根据波的起始点可以推算出它在询问点处的值（具体地，当这两个点的差模 $4$ 余 $0$ 的时候，贡献为 $a$；模 $4$ 余 $2$ 时，贡献为 $-a$；其余情况贡献为 $0$）。将所有波的贡献加起来即可。

另外，这题如果使用动态开点线段树的话可以做到 $O(q\log n)$，并且也是比较板的。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct wave
{
	int p,l,a;
}wv[4010];
signed main()
{
	int n,w,cnt=0;
	cin>>n>>w;
	for(int i=1;i<=n;i++)
	{
		char opt;
		cin>>opt;
		if(opt=='!')
		{
			cin>>wv[++cnt].p;
			cin>>wv[cnt].l>>wv[cnt].a;
		}
		else
		{
			int p;
			long long ans=0;
			cin>>p;
			for(int j=1;j<=cnt;j++)
			{
				if(wv[j].p+wv[j].l>p&&p>=wv[j].p)
				{
					int b=p-wv[j].p;
					b%=4;
					if(!b) ans+=wv[j].a;
					else if(b==2) ans-=wv[j].a;
				}
			}
			cout<<ans<<'\n';
		}
	}
}

---

