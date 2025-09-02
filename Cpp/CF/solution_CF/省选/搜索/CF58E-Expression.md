# Expression

## 题目描述

One day Vasya was solving arithmetical problems. He wrote down an expression $ a+b=c $ in his notebook. When the teacher checked Vasya's work it turned out that Vasya had solved the problem incorrectly. Now Vasya tries to find excuses. He says that he simply forgot to write down several digits in numbers $ a $ , $ b $ and $ c $ , but he can't remember what numbers they actually were. Help Vasya, find such numbers $ x $ , $ y $ and $ z $ , with which the following conditions are met:

- $ x+y=z $ ,
- from the expression $ x+y=z $ several digits can be erased in such a way that the result will be $ a+b=c $ ,
- the expression $ x+y=z $ should have the minimal length.

## 样例 #1

### 输入

```
2+4=5
```

### 输出

```
21+4=25
```

## 样例 #2

### 输入

```
1+1=3
```

### 输出

```
1+31=32
```

## 样例 #3

### 输入

```
1+1=2
```

### 输出

```
1+1=2
```

# 题解

## 作者：MilkyCoffee (赞：3)

难得有一道一次交就过的紫题，发现只有一篇题解，就来一篇。

解法是可行性剪枝的 dfs 。

当 $c = 0$ 时，显然我们只需要把 $c$ 的最高位处理成 $a+b+jw$ 就可以了。

当 $a,b,c$ 的个位相等时，根据乘法分配律我们需要处理下一位，注意这时位数需要加一。

对于其他情况，$a,b,c$ 中两项不变，枚举变的那一项，注意这时需要记录 $now$ 进行剪枝。

最后注意输入和输出用 `scanf` 和 `printf` 会比字符串拆分的代码短很多（但是我一开始写的是 string （

还有，预处理高位并存储在数组里会方便许多，不要学习我写了一半才想到预处理。

AC 代码：

```cpp
// jaco2567 AK IOI
// #include <bits/stdc++.h>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read() {
    int res = 0, F = 1;
    char k;
    while (!isdigit(k = getchar())) if (k == '-') F = -1;
    while (isdigit(k)) {
	  	res = res * 10 + k - '0';
        k = getchar();
    }
    return res * F;
}

inline void write(int x) {
    if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}

const int INF = 0x3f3f3f3f;

long long a, b, c, asa, asb, asc;
long long p[20];
int ans = INF;

void dfs(long long a, long long b, long long c, long long jw, long long na, 
	long long nb, long long nc, int now, int deep) {

	if (now >= ans) return;

	if (a == 0 && b == 0 && c == 0 && jw == 0) {
		// 没有需要加的数了 = 找到答案
		ans = now; asa = na; asb = nb; asc = nc;
		return ;
	}

	if (c == 0) { // 把 c 补上欠的数
		long long res = a + b + jw;
		int tmp = 0;
		while (res != 0) { tmp++; res /= 10; }

		dfs(0, 0, 0, 0, na + p[deep] * a, nb + p[deep] * b, 
			nc + p[deep] * (a + b + jw), now + tmp, deep + 1);
		
		return ;
	}

	if ((a + b + jw) % 10 == c % 10) { // 个位相等，处理高位

		dfs(a / 10, b / 10, c / 10, (a % 10 + b % 10 + jw) / 10, na + (a % 10) * p[deep], 
			nb + (b % 10) * p[deep], nc + (c % 10) * p[deep], now, deep + 1);
		
		return ;
	}

	dfs(a * 10 + (c % 10 - b % 10 - jw + 10) % 10, b, c, jw, na, nb, nc, now + 1, deep); // 加 a
	dfs(a, b * 10 + (c % 10 - a % 10 - jw + 10) % 10, c, jw, na, nb, nc, now + 1, deep); // 加 b
	dfs(a, b, c * 10 + (a % 10 + b % 10 + jw) % 10, jw, na, nb, nc, now + 1, deep); // 加 c
}

int main() {
	scanf("%lld+%lld=%lld", &a, &b, &c);

	p[0] = 1;
	for (int i = 1; i <= 18; i++) {
		p[i] = p[i-1] * 10;
	}

	dfs(a, b, c, 0, 0, 0, 0, 0, 0);

	printf("%lld+%lld=%lld", asa, asb, asc);

	return 0;
}

```

---

## 作者：Laoshan_PLUS (赞：2)

## [[CF58E] Expression](https://www.luogu.com.cn/problem/CF58E)

上面的题解说的都不怎么详细。虽然是道搜索题，但是不能胡搜，搜的思路还是值得学习的。

首先需要明确，为了使最终的答案尽可能短，我们应该**尽可能少地**创造新的数位，所以盲目枚举左右两边加什么数是不可取的，我们应该**从低位向高位依次判断**。

搜到当前位时，分为两种情况：当前位满足要求、当前位不满足要求。若当前位满足要求，我们就不需要再考虑当前位了，开始考虑高位，所以我们给当前循环的 $a,b,c$ 全部 $\div10$；若当前位不满足要求，我们再一一枚举 $a,b,c$，给 $a,b,c$ 的最后一位加上一个数字然后继续搜。同样是因为我们应该尽可能少地创造新的数位，所以一旦我们给一个数的最后一位加上一个数字 $i$（即 $a\gets a\times10+i$，$b,c$ 同理），这个 $i$ 直接就是 $c$ 和 $b$ 的个位的差值。同理，如果是 $b$ 就是 $c$ 和 $a$ 的个位的差值，$c$ 就是 $a$ 与 $b$ 的个位的和。别忘了考虑进位。

需要特判的是当 $c=0$ 时，这时我们只需要将 $c$ 的最高位处理成 $a+b+\text{进位}$ 即可。

代码和 $\textsf{MilkyCoffee}$ 的差不多，就不贴了。

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF58E)

设 $f_{a,b,c,d}$ 表示第一个数对上了后 $a$ 位，第二个数对上了后 $b$ 位，第三个数对上了后 $c$ 位，且进位为 $d$ 的最小操作次数。

直接三层循环枚举这一位填的值。

然后会发现无法处理前导零，那就再加 $3$ 维 $0/1$，表示每个数当前是否在填前导零。

输出方案直接记录路径即可。

$9$ 层循环，喜提最劣解。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int a,b,c,f[2][2][2][55][55][55][2],n,pw[55],r1,r2,r3,ans1,ans2,ans3,ops;
struct node{
    int n1,n2,n3,a,b,c,d;
}lst[2][2][2][55][55][55][2];
void solve(int t1,int t2,int t3,int aq,int bq,int cq,int d){
    if(aq==0&&bq==0&&cq==0)return;
    node cc=lst[t1][t2][t3][aq][bq][cq][d];
    int k1=cc.a==10,k2=cc.b==10,k3=cc.c==10;
    if(cc.a==10)cc.a=a/pw[aq-1]%10;
    if(cc.b==10)cc.b=b/pw[bq-1]%10;
    if(cc.c==10)cc.c=c/pw[cq-1]%10;
    ans1=ans1*10+cc.a,ans2=ans2*10+cc.b,ans3=ans3*10+cc.c;
    solve(cc.n1,cc.n2,cc.n3,aq-k1,bq-k2,cq-k3,cc.d);
}
signed main(){
    cin>>s;
    int nw=0;
    for(int i=0;i<s.size();i++){
        if(s[i]=='+'){
            a=nw;
            nw=0;
        }else if(s[i]=='='){
            b=nw;
            nw=0;
        }else{
            nw=nw*10+s[i]-'0';
        }
    }
    if(a<b)ops=1,swap(a,b);
    pw[0]=1;
    n=18;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10;
    c=nw;
    memset(f,0x3f,sizeof(f));
    f[0][0][0][0][0][0][0]=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                if(i==0&&j==0&&k==0)continue;
                for(int t1=0;t1<=1;t1++)for(int t2=0;t2<=1;t2++)for(int t3=0;t3<=1;t3++){
                int ans0=1e9,ans1=1e9;
                for(int i1=0;i1<=10;i1++){
                    for(int i2=0;i2<=10;i2++){
                        for(int i3=0;i3<=10;i3++){
                            int nd=3,aa=i1,bb=i2,cc=i3,n1=t1,n2=t2,n3=t3;
                            if(i==0&&i1==10)continue;
                            if(j==0&&i2==10)continue;
                            if(k==0&&i3==10)continue;
                            if(i1==10&&pw[i-1]>a&&!t1)nd++;
                            if(i2==10&&pw[j-1]>b&&!t2)nd++;
                            if(i3==10&&pw[k-1]>c&&!t3)nd++;
                            if(i1==10)aa=a/pw[i-1]%10,nd--;
                            if(i2==10)bb=b/pw[j-1]%10,nd--;
                            if(i3==10)cc=c/pw[k-1]%10,nd--;
                            if(aa)n1=0;
                            if(bb)n2=0;
                            if(cc)n3=0;
                            if((aa+bb)%10==cc){
                                if(aa+bb>=10){
                                    if(f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][0]+nd<ans1)ans1=f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][0]+nd,lst[t1][t2][t3][i][j][k][1]=(node){n1,n2,n3,i1,i2,i3,0};
                                }else{
                                    if(f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][0]+nd<ans0)ans0=f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][0]+nd,lst[t1][t2][t3][i][j][k][0]=(node){n1,n2,n3,i1,i2,i3,0};
                                }
                            }else if((aa+bb+1)%10==cc){
                                if(aa+bb+1>=10){
                                    if(f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][1]+nd<ans1)ans1=f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][1]+nd,lst[t1][t2][t3][i][j][k][1]=(node){n1,n2,n3,i1,i2,i3,1};
                                }else{
                                    if(f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][1]+nd<ans0)ans0=f[n1][n2][n3][i-(i1==10)][j-(i2==10)][k-(i3==10)][1]+nd,lst[t1][t2][t3][i][j][k][0]=(node){n1,n2,n3,i1,i2,i3,1};
                                }
                            }
                        }
                    }
                }
                f[t1][t2][t3][i][j][k][0]=ans0,f[t1][t2][t3][i][j][k][1]=ans1;
                }
            }
        }
    }
    int as=log(a)+1,bs=log(b)+1,cs=log(c)+1;
    r1=as,r2=bs,r3=cs;
    for(int i=as;i<=n;i++){
        for(int j=bs;j<=n;j++){
            for(int k=cs;k<=n;k++){
                if(f[1][1][1][i][j][k][0]<f[1][1][1][r1][r2][r3][0])r1=i,r2=j,r3=k;
            }
        }
    }
    solve(1,1,1,r1,r2,r3,0);
  if(ops)swap(ans1,ans2);
    cout<<ans1<<"+"<<ans2<<"="<<ans3;
}
```


---

## 作者：Itst (赞：1)

#### 一道略难但比较好的搜索题emm
#### 思路与P1092虫食算类似
#### 先检索a、b、c三个数的个位如果满足a%10+b%10+jw-c==0or10则不需要再加数即可检索下一位
#### 否则在a或b或c上加一个数满足上式（为何不加两个数？因为加一个数的情况已经包含了加两个数的情况），再检索下一位
#### 至于比较坑的点就是对0的处理
#### 如果通过搜索导致c已经没有更多的位数了，则只能在c上加数字（存在两个正整数的和小于这两个正整数吗？）
#### 而如果搜索到a没有位数或b没有位数的情况，则需要一个标记记录是否在a或b上再加位数（不这样很有可能忽略加0的情况啊qwq）
#### 再加一个最优化剪枝就能出解惹
------------
#### 接下来欢迎欣赏我思路混乱的代码QAQ
```cpp
#include<bits/stdc++.h>
using namespace std;
int now[15][3] , ans[15][3] , nA , nB , nC , minN = 12 , cnt , t[13];
//now是当前加了哪些数
//ans是最终答案加了哪些数
void dfs(int a , int b , int c , int num , int jw , int cou , bool ifA , bool ifB){
//abc记录当前三个数还有多少没有算
//num记录加了几个数
//cou表示加法共有几位
//ifA与ifB表示是否还能够再a或b上加数
	if(!a && !b && !c && !jw){
		minN = num;
		cnt = cou;
		memcpy(ans , now , sizeof(now));
		return;
	}
    //注意：下面的四个dfs前的if中的条件都有c!=0！！！
	if(a % 10 + b % 10 - c % 10 + jw == 0 && c)
		dfs(a / 10 , b / 10 , c / 10 , num , 0 , cou + 1 , a ? 0 : 1 , b ? 0 : 1);
	else	if(a % 10 + b % 10 - c % 10 + jw == 10 && c)
		dfs(a / 10 , b / 10 , c / 10 , num , 1 , cou + 1 , a ? 0 : 1 , b ? 0 : 1);
	else{
		if(minN - ++num <= 0)	return;
		now[num][2] = ++cou;
		if(!ifA && c){
			now[num][0] = 1;
			now[num][1] = (c % 10 - b % 10 - jw + 10) % 10;
			bool f = ifB;
			if(!b)	ifB = 1;
			dfs(a , b / 10 , c / 10 , num , (now[num][1] + b % 10 + jw - c % 10) / 10 , cou , ifA , ifB);
			ifB = f;
		}
		if(!ifB && c){
			now[num][0] = 2;
			now[num][1] = (c % 10 - a % 10 + 10 - jw) % 10;
			bool f = ifA;
			if(a == 0)	ifA = 1;
			dfs(a / 10 , b , c / 10 , num , (now[num][1] + a % 10 + jw - c % 10) / 10 , cou , ifA , ifB);
			ifA = f;
		}
		now[num][0] = 3;
		now[num][1] = (a % 10 + b % 10 + jw) % 10;
		if(!a)	ifA = 1;
		if(!b)	ifB = 1;
		dfs(a / 10 , b / 10 , c , num , (a % 10 + b % 10 + jw - now[num][1]) / 10 , cou , ifA , ifB);
	}
}
int main(){
	int a , b , c;
	bool f;
	scanf("%d+%d=%d" , &a , &b , &c);
	dfs(a , b , c , 0 , 0 , 0 , 0 , 0);
	//一个很迷的输出
    int p = 1;
	while(p <= minN && ans[p][0] - 1)	p++;
	for(int i = 1 ; i <= cnt ; i++)
		if(p <= minN && ans[p][2] == i){
			t[i] = ans[p++][1];
			while(p <= minN && ans[p][0] - 1)	p++;
		}
		else{
			t[i] = a % 10;
			a /= 10;
		}
	f = 0;
	for(int i = cnt ; i ; i--)
		if(f || t[i]){
			putchar(t[i] + '0');
			f = 1;
		}
	putchar('+');
	p = 1;
	while(p <= minN && ans[p][0] - 2)	p++;
	for(int i = 1 ; i <= cnt ; i++)
		if(p <= minN && ans[p][2] == i){
			t[i] = ans[p++][1];
			while(p <= minN && ans[p][0] - 2)	p++;
		}
		else{
			t[i] = b % 10;
			b /= 10;
		}
	f = 0;
	for(int i = cnt ; i ; i--)
		if(f || t[i]){
			putchar(t[i] + '0');
			f = 1;
		}
	putchar('=');
	p = 1;
	while(p <= minN && ans[p][0] - 3)	p++;
	for(int i = 1 ; i <= cnt ; i++)
		if(p <= minN && ans[p][2] == i){
			t[i] = ans[p][1];
			p++;
			while(p <= minN && ans[p][0] - 3)	p++;
		}
		else{
			t[i] = c % 10;
			c /= 10;
		}
	f = 0;
	for(int i = cnt ; i ; i--)
		if(f || t[i]){
			putchar(t[i] + '0');
			f = 1;
		}
	return 0;
}
```

---

