# Three Logos

## 题目描述

三家公司决定订购一个带有其标志图片的正方形广告牌。每个公司的徽标是一个非空的矩形。

只有当广告牌上可以放置所有三个徽标且不重叠、没有剩余空白时，广告商才会张贴广告。当然，徽标的两侧与广告牌的两侧平行。

您的任务是确定是否有可能在不违反任何规定的情况下，将所有三家公司的徽标放置在某个方形广告牌上。

## 样例 #1

### 输入

```
5 1 2 5 5 2
```

### 输出

```
5
AAAAA
BBBBB
BBBBB
CCCCC
CCCCC
```

## 样例 #2

### 输入

```
4 4 2 6 4 2
```

### 输出

```
6
BBBBBB
BBBBBB
AAAACC
AAAACC
AAAACC
AAAACC
```

# 题解

## 作者：过氧化氢_syq0057 (赞：1)

乍一看毫无头绪，仔细想想其实很简单。

无非两种情况：

$(1)$、`A`，`B`，`C` 各占一块（长都相等），如样例 $1$：
```
AAAAA
BBBBB
BBBBB
CCCCC
CCCCC
```
$(2)$、`A`，`B`，`C` 呈三权分立状（一包二），如样例 $2$：
```
BBBBBB
BBBBBB
AAAACC
AAAACC
AAAACC
AAAACC
```
没有其他情况，说有的话旋转一下也就回到这两种情况了。

样例其实就很全了，一下觉得应该是橙而不是黄 /jy。

用 $a_1,a_2$ 表示 `A` 块的长和宽，用 $a_3,a_4$ 表示 `B` 块的长和宽，用 $a_5,a_6$ 表示 `C` 块的长和宽。

满足情况 $(1)$ 直接输出，情况 $(2)$ 枚举，互换长宽（这里是不打破定义了 /jk）。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 100005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int a[7];
bool flag;
void change(int &x, int &y) {
	x ^= y ^= x ^= y;
}
void dfs(int x) {
	if (x == 4) {
		if (a[1] == a[3] + a[5] && a[4] == a[6] && a[2] + a[6] == a[1]) {
			flag = 1;
			printf("%d\n", a[1]);
			for (int i=1; i<=a[2]; i++) {
				for (int j=1; j<=a[1]; j++)
					putchar('A');
				printf("\n");
			}
			for (int i=1; i<=a[4]; i++) {
				for (int j=1; j<=a[3]; j++)
					putchar('B');
				for (int j=1; j<=a[5]; j++)
					putchar('C');
				printf("\n");
			}
		}//A在上面
		else if (a[3] == a[1] + a[5] && a[2] == a[6] && a[4] + a[6] == a[3]) {
			flag = 1;
			printf("%d\n", a[3]);
			for (int i=1; i<=a[4]; i++) {
				for (int j=1; j<=a[3]; j++)
					putchar('B');
				printf("\n");
			}
			for (int i=1; i<=a[2]; i++) {
				for (int j=1; j<=a[1]; j++)
					putchar('A');
				for (int j=1; j<=a[5]; j++)
					putchar('C');
				printf("\n");
			}
		}//B在上面
		else if (a[5] == a[1] + a[3] && a[2] == a[4] && a[2] + a[6] == a[5]) {
			flag = 1;
			printf("%d\n", a[5]);
			for (int i=1; i<=a[6]; i++) {
				for (int j=1; j<=a[5]; j++)
					putchar('C');
				printf("\n");
			}
			for (int i=1; i<=a[4]; i++) {
				for (int j=1; j<=a[1]; j++)
					putchar('A');
				for (int j=1; j<=a[3]; j++)
					putchar('B');
				printf("\n");
			}
		}//C在上面
		return ;
	}
	dfs(x + 1);
	if (flag) return ;
	change(a[(x << 1) - 1], a[x << 1]);
	dfs(x + 1);
	change(a[(x << 1) - 1], a[x << 1]);//回溯
	if (flag) return ;
}
int main() {
	for (int i=1; i<=6; i++)
		scanf("%d", &a[i]);
	if (a[1] < a[2]) change(a[1], a[2]);
	if (a[3] < a[4]) change(a[3], a[4]);
	if (a[5] < a[6]) change(a[5], a[6]);
	if (a[1] == a[3] && a[3] == a[5] && a[2] + a[4] + a[6] == a[1]) {
		printf("%d\n", a[1]);
		for (int i=1; i<=a[2]; i++) {
			for (int j=1; j<=a[1]; j++)
				putchar('A');
			printf("\n");
		}
		for (int i=1; i<=a[4]; i++) {
			for (int j=1; j<=a[3]; j++)
				putchar('B');
			printf("\n");
		}
		for (int i=1; i<=a[6]; i++) {
			for (int j=1; j<=a[5]; j++)
				putchar('C');
			printf("\n");
		}
	}//满足情况(1)
	else {
		dfs(1);//搜索，看是否满足情况(2)
		if (!flag) printf("-1\n");//都不满足，输出-1
	}
	return 0;
}
```

完结散花 qaq

---

## 作者：ZLCT (赞：0)

# CF581D Three Logos
## 题目翻译
给定三个矩形长宽分别为 $x_i,y_i$，求一种合法方案使的这三个矩形通过评议旋转组成一个正方形（不能有空隙和重叠）。
## solution
这个题有一个关键的性质就是不能有空隙和重叠，这就代表新的正方形的面积一定等于原来三个矩形面积只和。\
那么假设原来矩形面积不是个完全平方数，那一定没有一个合法的正方形，否则正方形的边长一定是 $\sqrt{\sum S_i}$，其中 $S_i$ 表示第 $i$ 个矩形的面积。\
那么确定好正方形的面积之后，我们就可以摆放我们的三个矩形了。\
我们这里设 $l$ 代表正方形边长。\
经过自己手动摆放会发现如果最终有合法摆放，一定只有两种情况：\
第一种情况，三个矩形的长边都是 $l$，由于我们保证了面积之和是 $l^2$，所以三个矩形的宽边一定满足 $y_1+y_2+y_3=l$，这一点十分好推，因为 $l^2=x_1\times y_1+x_2\times y_2+x_3\times y_3$，而 $x_1=x_2=x_3=l$，所以两边同时除以 $l$，就变成了 $l=y_1+y_2+y_3$。\
第二种情况就是有一个矩形形如 $l\times c$，那么此时相当于另外两个矩形要构成一个 $l\times(l-c)$ 的大矩形，这里看似是两种情况，分别是左右摆放和上下摆放，但是上下摆放已经归为第一种情况了，所以只剩第二种情况了。\
由于这是一个正方形，所以把正方形旋转后不会产生全新的摆放，严谨说明就是正方形旋转群若只能旋转 $90k$ 度，那么整个群里只有幺元一个元素。\
这道题唯一麻烦的地方在于你确定了第一块拼图以后剩下两块拼图的横竖需要进一步判断。但是这一点我没有找到更为优雅的方法去处理。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,len,ans[114][114],last=6;
struct node{
    int x,y,id;
    bool operator <(node c1)const{
        return x>c1.x;
    }
}a[3];
signed main(){
    for(int i=0;i<3;++i){
        cin>>a[i].x>>a[i].y;
        if(a[i].x<a[i].y)swap(a[i].x,a[i].y);
        sum+=a[i].x*a[i].y;
        a[i].id=i+1;
    }
    len=sqrt(sum);
    if(len*len!=sum){
        cout<<"-1\n";
        return 0;
    }
    sort(a,a+3);
    if(a[0].x!=len){
        cout<<"-1\n";
        return 0;
    }
    for(int i=1;i<=a[0].y;++i){
        for(int j=1;j<=len;++j){
            ans[i][j]=a[0].id;
        }
    }
    last-=a[0].id;
    if(a[1].x==len){
        last-=a[1].id;
        for(int i=a[0].y+1;i<=a[0].y+a[1].y;++i){
            for(int j=1;j<=len;++j){
                ans[i][j]=a[1].id;
            }
        }
        for(int i=1;i<=len;++i){
            for(int j=1;j<=len;++j){
                if(!ans[i][j])ans[i][j]=last;
            }
        }
        cout<<len<<"\n";
        for(int i=1;i<=len;++i){
            for(int j=1;j<=len;++j){
                if(ans[i][j]==1)cout<<"A";
                else if(ans[i][j]==2)cout<<"B";
                else cout<<"C";
            }
            cout<<'\n';
        }
        return 0;
    }
    if(a[1].x==a[2].y||a[1].y==a[2].x)swap(a[1].x,a[1].y);
    if(a[1].x==a[2].x&&(a[1].y+a[2].y)==len){
        last-=a[1].id;
        for(int j=1;j<=a[1].y;++j){
            for(int i=a[0].y+1;i<=len;++i){
                ans[i][j]=a[1].id;
            }
        }
    }else if(a[1].y==a[2].y&&(a[1].x+a[2].x)==len){
        swap(a[1].x,a[1].y);swap(a[2].x,a[2].y);
        last-=a[1].id;
        for(int j=1;j<=a[1].y;++j){
            for(int i=a[0].y+1;i<=len;++i){
                ans[i][j]=a[1].id;
            }
        }
    }else{
        cout<<"-1\n";
        return 0;
    }
    for(int i=1;i<=len;++i){
        for(int j=1;j<=len;++j){
            if(!ans[i][j])ans[i][j]=last;
        }
    }
    cout<<len<<"\n";
    for(int i=1;i<=len;++i){
        for(int j=1;j<=len;++j){
            if(ans[i][j]==1)cout<<"A";
            else if(ans[i][j]==2)cout<<"B";
            else cout<<"C";
        }
        cout<<'\n';
    }
}
```

---

## 作者：nxd_oxm (赞：0)

# 题意
题目说有三块长方形板子，让我们毫无空隙的贴到一个正方形上去。第一块占用的位置输出 ``A``，第二块输出 ``B``，第三块输出 ``C``。

然后给了他们分别的长宽，让我们输出可能的情况。如果不行就输出 ``-1``。

## 样例 #1

### 样例输入 #1

```
5 1 2 5 5 2
```

### 样例输出 #1

```
5
AAAAA
BBBBB
BBBBB
CCCCC
CCCCC
```

# 思路

思路其实很简单。

因为我们把板子放入正方形时，只有如下两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/mf5mydzq.png)

非常明了了，只需要加一堆判断。

当 $x1 = x2 = x3$，且 $x1 = y1 + y2 + y3$ 即图一时，输出当前情况。

当 $x1 = x2 + x3$，$y2 = y3$ 且 $x1 = y1 + y2$ 即图二时，输出当前情况。

但我们要讨论三块板子的顺序问题，也就是全排列，排列之后再判断。还要注意上图可以翻转，旋转，板子也可以，所以还要讨论板子长宽的全排列。

![](https://cdn.luogu.com.cn/upload/image_hosting/qoc5m2sw.png)

记得输出没有解法时的情况。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int x1,y1,x2,y2,x3,y3;
bool ok=false;
char f[4];
void dfs(int k){
	if(ok){
		return;
	}
	if(k>3){
		if(x1==x2&&x2==x3&&y1+y2+y3==x1){
			cout<<x1<<endl;
			f(i,1,y1){
				f(j,1,x1){
					cout<<f[1];
				}
				cout<<endl;
			}
			f(i,1,y2){
				f(j,1,x1){
					cout<<f[2];
				}
				cout<<endl;
			}
			f(i,1,y3){
				f(j,1,x1){
					cout<<f[3];
				}
				cout<<endl;
			}
			ok=1;
		}
		if(x1==x2+x3&&y2==y3&&y1+y2==x1){
			cout<<x1<<endl;
			f(i,1,y1){
				f(j,1,x1){
					cout<<f[1];
				}
				cout<<endl;
			}
			f(i,1,y2){
				f(j,1,x2){
					cout<<f[2];
				}
				f(j,1,x3){
					cout<<f[3];
				}
				cout<<endl;
			}
			ok=1;
		}
		return;
	}
	dfs(k+1);
	if(k==1)swap(x1,y1);
	if(k==2)swap(x2,y2);
	if(k==3)swap(x3,y3);
	dfs(k+1);
}
int ax1,ay1,ax2,ay2,ax3,ay3;
void cc(){
	x1=ax1;
	y1=ay1;
	x2=ax2;
	y2=ay2;
	x3=ax3;
	y3=ay3;
}
void qq(){
	ax1=x1;
	ay1=y1;
	ax2=x2;
	ay2=y2;
	ax3=x3;
	ay3=y3;
}
signed main(){
	cin>>x1>>y1>>x2>>y2>>x3>>y3;
	
	//A B C
	f[1]='A',f[2]='B',f[3]='C';
	qq();
	dfs(1);
	
	//A C B
	f[1]='A',f[2]='C',f[3]='B';
	cc();
	swap(x2,x3),swap(y2,y3);
	qq();
	dfs(1);
	
	//B C A 
	f[1]='B',f[2]='C',f[3]='A';
	cc();
	swap(x1,x3),swap(y1,y3);
	qq();
	dfs(1);
	
	//B A C
	f[1]='B',f[2]='A',f[3]='C';
	cc();
	swap(x2,x3),swap(y2,y3);
	qq();
	dfs(1);
	
	//C A B
	f[1]='C',f[2]='A',f[3]='B';
	cc();
	swap(x1,x3),swap(y1,y3);
	qq();
	dfs(1);
	
	//C B A
	f[1]='C',f[2]='B',f[3]='A';
	cc();
	swap(x2,x3),swap(y2,y3);
	qq();
	dfs(1);
	
	if(!ok){
		cout<<-1;
	}
	return 0;
}

```

---

## 作者：djwj323 (赞：0)

三个矩形覆盖方式大致可分为两种：两面包夹芝士与三足鼎立。

![](https://cdn.luogu.com.cn/upload/image_hosting/ifder6bx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)![](https://cdn.luogu.com.cn/upload/image_hosting/aubmkat7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

思路很简单，但要加一堆~~恶心的~~判断。

```cpp
#include<iostream> 
using namespace std;
long long x[4],y[4],s,_,f,i,j;
int main()
{
    scanf("%lld%lld%lld%lld%lld%lld",&x[1],&y[1],&x[2],&y[2],&x[3],&y[3]),s=x[1]*y[1]+x[2]*y[2]+x[3]*y[3],_=sqrt(s);
    if(_*_!=s)  printf("-1");
    else
    {
        if(x[1]==_)  swap(x[1],y[1]),f=1;
        else if(y[1]==_)  f=1;
        if(x[2]==_)  swap(x[2],y[2]),f=2;
        else if(y[2]==_)  f=2;
        if(x[3]==_)  swap(x[3],y[3]),f=3;
        else if(y[3]==_)  f=3;
        if(y[1]==_&&y[2]==_&&y[3]==_)
        {
            cout<<_<<endl;
            for(i=1;i<=x[1];i++)
            {
                for(j=1;j<=_;j++)  cout<<'A';
                cout<<endl;
            }
            for(i=1;i<=x[2];i++)
            {
                for(j=1;j<=_;j++)  cout<<'B';
                cout<<endl;
            }
            for(i=1;i<=x[3];i++)
            {
                for(j=1;j<=_;j++)  cout<<'C';
                cout<<endl;
            }
        }
        else if(f==1)
        {
            cout<<_<<endl;
            if(x[2]==y[3])  swap(x[3],y[3]);
            else if(x[3]==y[2])  swap(x[2],y[2]);
            else if(y[2]==y[3])  swap(x[2],y[2]),swap(x[3],y[3]);
            if(x[2]==x[3]&&x[1]+x[2]==_&&y[2]+y[3]==_)
            {
                for(i=1;i<=x[3];i++)
                {
                    for(j=1;j<=_;j++)
                    {
                        if(j<=y[2])  cout<<'B';
                        else  cout<<'C';
                    }
                    cout<<endl;
                }
                for(i=1;i<=x[1];i++)
                {
                    for(j=1;j<=_;j++)  cout<<'A';
                    cout<<endl;
                }
            }
            else  printf("-1");
        }
        else if(f==2)
        {
            cout<<_<<endl;
            if(x[1]==y[3])  swap(x[3],y[3]);
            else if(x[3]==y[1])  swap(x[1],y[1]);
            else if(y[1]==y[3])  swap(x[1],y[1]),swap(x[3],y[3]);
            if(x[1]==x[3]&&x[2]+x[3]==_&&y[1]+y[3]==_)
            {
                for(i=1;i<=x[1];i++)
                {
                    for(j=1;j<=_;j++)
                    {
                        if(j<=y[1])  cout<<'A';
                        else  cout<<'C';
                    }
                    cout<<endl;
                }
                for(i=1;i<=x[2];i++)
                {
                    for(j=1;j<=_;j++)  cout<<'B';
                    cout<<endl;
                }
            }
            else  printf("-1");
        }
        else if(f==3)
        {
            cout<<_<<endl;
            if(x[1]==y[2])  swap(x[2],y[2]);
            else if(x[2]==y[1])  swap(x[1],y[1]);
            else if(y[1]==y[2])  swap(x[1],y[1]),swap(x[2],y[2]);
            if(x[1]==x[2]&&x[3]+x[1]==_&&y[1]+y[2]==_)
            {
                for(i=1;i<=x[2];i++)
                {
                    for(j=1;j<=_;j++)
                    {
                        if(j<=y[1])  cout<<'A';
                        else  cout<<'B';
                    }
                    cout<<endl;
                }
                for(i=1;i<=x[3];i++)
                {
                    for(j=1;j<=_;j++)  cout<<'C';
                    cout<<endl;
                }
            }
            else  printf("-1");
        }
        else  printf("-1");
    }
}
```


---

