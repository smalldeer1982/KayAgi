# [CCC 2008 S4] Twenty-four

## 题目描述

二十四点是一种流行的纸牌游戏，适合四名玩家进行。每位玩家会得到一副牌，牌面朝下。在每一轮中，每位玩家翻开自己牌堆顶的一张牌，使其对所有人可见。目标是使用这些牌的值（其中 $A$ 表示 $1$，$J$ 表示 $11$，$Q$ 表示 $12$，$K$ 表示 $13$）找到一个算术表达式，使其结果为 $24$。例如，在示例中，一个可能的表达式是：

$((A \times K) - J) \times Q$

$((1 \times 13) - 11) \times 12$

第一个找到这样表达式的玩家赢得这一轮，并将四张牌放到自己牌堆的底部。

每个有效的算术表达式必须使用所有四张牌，并且必须通过加法、减法、乘法或除法组合它们的值。允许使用括号来指定运算的优先级。不能将牌并列以构成多位十进制数（例如，不能将牌 $2$ 和 $4$ 并列以形成 $24$）。不允许非整数的除法结果，即使是作为整体表达式的子表达式的部分结果。

在某些情况下，玩家可能需要很长时间才能找到一个结果为 $24$ 的表达式。实际上，在某些情况下，不存在这样的表达式。你的任务是给定四张牌，找出一个结果为小于或等于 $24$ 的最大数的表达式。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
3
3
3
3
1
1
1
1
12
5
13
1```

### 输出

```
24
4
21```

# 题解

## 作者：Milthm (赞：2)

题目就是求 $24$ 点，只是还多了个求不出来的情况。

这个时候我们应该拿出 [P1834 题解](https://www.luogu.com.cn/blog/feixika/solution-p1834)，然后你就会发现是两题差不多的（只是不知道为什么难度差这么多）。

方法我在这篇题解里也写了，就是全排列枚举，然后暴力枚举符号。

然后取最大值的时候记得判断是否大于 $24$。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5],f,ans; 
int calc(int x,int y,int op){
    if(op==0)return x+y;
    if(op==1)return x-y;
    if(op==2)return x*y;
    if(op==3&&y!=0&&x%y==0)return x/y;
    f=1;return 0;
}
int main(){
	cin>>n;
	while(n--){
		ans=0;
		for(int i=1;i<=4;++i)cin>>a[i];
		do{
			for(int i=0;i<4;++i){
				for(int j=0;j<4;++j){
					for(int k=0;k<4;++k){
						f=0;int x=calc(calc(calc(a[1],a[2],i),a[3],j),a[4],k);
						if(f==0&&x<=24)ans=max(ans,x);
						f=0;x=calc(calc(a[1],calc(a[2],a[3],j),i),a[4],k);
						if(f==0&&x<=24)ans=max(ans,x);
						f=0;x=calc(a[1],calc(a[2],calc(a[3],a[4],k),j),i);
						if(f==0&&x<=24)ans=max(ans,x);
						f=0;x=calc(calc(a[1],a[2],i),calc(a[3],a[4],k),j);
						if(f==0&&x<=24)ans=max(ans,x);
						f=0;x=calc(a[1],calc(calc(a[2],a[3],j),a[4],k),i);
						if(f==0&&x<=24)ans=max(ans,x);
					}
				}
			}
		}while(next_permutation(a+1,a+5));
		cout<<ans<<'\n';
	} 
	return 0;
}

```


---

## 作者：ivyjiao (赞：2)

题意就不简述了，注意如果不能整除是不能进行除法操作的（不然样例都过不去）。

这里我们不讲正解，讲一个叫随机贪心的算法。

每次将原来的四个数 random_shuffle 一下，每次的运算也是随机的。

注意一下这里有**本质不同**的两种运算方法（`⊕` 表示任意一种运算符号）：

```
a⊕b⊕c⊕d
```

```
(a⊕b)⊕(c⊕d)
```

这两种方法不能通过 random_shuffle 互相变化得到，所以要分别进行贪心。

**注意不要出现除以零或者取模零的情况**。

优化：如果某一次贪心之后结果已经是 $24$ 了，就可以结束贪心并输出了，能节省时间。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int t,a[5],b,cnt,cnt1,cnt2,ans,boo;
int main(){
    srand(time(0));
    cin>>t;
    for(int j=1;j<=t;j++){
        ans=0;
        boo=0;
        for(int i=1;i<=4;i++) cin>>a[i];
        while((double)clock()/CLOCKS_PER_SEC<0.99/t*j){
            random_shuffle(a+1,a+5);
            cnt1=0;
            if(a[1]%a[2]==0) b=rand()%4;
            else b=rand()%3;
            if(b==0) cnt1=a[1]+a[2];
            else if(b==1) cnt1=a[1]-a[2];
            else if(b==2) cnt1=a[1]*a[2];
            else cnt1=a[1]/a[2];
            cnt2=0;
            if(a[3]%a[4]==0) b=rand()%4;
            else b=rand()%3;
            if(b==0) cnt2=a[3]+a[4];
            else if(b==1) cnt2=a[3]-a[4];
            else if(b==2) cnt2=a[3]*a[4];
            else cnt2=a[3]/a[4];
            if(cnt2!=0){
                if(cnt1%cnt2==0) b=rand()%4;
                else b=rand()%3;
                if(b==0) cnt=cnt1+cnt2;
                else if(b==1) cnt=cnt1-cnt2;
                else if(b==2) cnt=cnt1*cnt2;
                else cnt=cnt1/cnt2;
                if(cnt<=24) ans=max(cnt,ans);
                if(ans==24){
                    puts("24");
                    boo=1;
                    break;
                }
            }
            cnt=a[1];
            for(int i=2;i<=4;i++){
                if(cnt%a[i]==0) b=rand()%4;
                else b=rand()%3;
                if(b==0) cnt+=a[i];
                else if(b==1) cnt-=a[i];
                else if(b==2) cnt*=a[i];
                else cnt/=a[i];
            }
            if(cnt<=24) ans=max(cnt,ans);
            if(ans==24){
                puts("24");
                boo=1;
                break;
            }
        }
        if(!boo) cout<<ans<<endl;
    }
}
```

---

## 作者：_hud (赞：1)

# 题解：[P9861 \[CCC 2008 S4\] Twenty-four](https://luogu.com.cn/problem/P9861)

## 思路

Python 大法好。

由题意，数据量较小，可以使用全排列。枚举全排列后容易我们知道答案必定属于下面两种形式之一：`a {} b {} c {} d` 和 `(a {} b) {} (c {} d)`。故枚举符号，取小于 $24$ 的最大值即可。

接下来再来讲讲如何实现。Python 库 `itertools` 提供的函数可以用于全排列以及枚举符号，而 `eval` 函数可以直接对表达式求值。具体可以看代码。

## 代码

```py
from itertools import permutations, product
n = int(input())
for qwq in range(n):
    res = 0 # 保存小于 24 的最大值
    for a, b, c, d in permutations((int(input()) for _ in range(4))): # 枚举全排列
        for s in ('(((a{}b){}c){}d)', '((a{}b){}(c{}d))'): # 枚举两种括号形式
            for ops in product('+-*/', repeat = 3): # 枚举运算符
                calc = s.format(*ops)
                try: ans = eval(calc) # 防止除 0 的情况
                except: continue
                try:
                    if ans > res and ans <= 24 and eval(calc.replace('/', '//')) == ans: # 这里是为了判断是否整除
                        res = ans 
                except: continue
    print(int(res)) 
```

---

## 作者：Tracy_Loght (赞：1)

## 思路：

显然，由于字典序尽量小，显然括号的字典序是最小的，所以括号能打就打，对于每一个形如 `a?b` 的式子，都需要加上括号，变为 `(a?b)`。

考虑枚举所有可能的算式，发现只有这仅仅五种不同的符合条件的方式：

`(a?(b?(c?d)))`

`(a?((b?c)?d))`

`((a?(b?c))?d)`

`((a?b)?(c?d))`

`(((a?b)?c)?d)`

其中的字母代表数字，问号代表符号。

考虑枚举符号和数字的顺序，将所有符合条件的加入答案中，最后排序即可。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,n,k,v[10],zxy[10],p_zl[20010];
char zl[20010][30],upp[5]={'0','+','-','*','/'};
ll mest(ll x,ll u,ll y){
	if(u==1) return x+y;
	else if(u==2) return x-y;
	else if(u==3) return x*y;
	else if(y==0) return -817;
	else if(u==4&&x%y==0) return x/y;
	else if(u==4&&x%y!=0) return -817;
}
int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	cin>>t;
	while(t--){
		for(ll i=1;i<=20000;i++) p_zl[i]=0;
		for(ll i=1;i<=9;i++) v[i]=0;
		for(ll i=1;i<=9;i++) zxy[i]=0;
		for(ll i=1;i<=20000;i++)
			for(ll j=1;j<=20;j++)
				zl[i][j]='#';
		n=4;k=0;
		for(ll i=1;i<=n;i++) cin>>v[i];
		for(ll w1=1;w1<=4;w1++){
			for(ll w2=1;w2<=4;w2++){
				for(ll w3=1;w3<=4;w3++){
					for(ll w4=1;w4<=4;w4++){
						if( w1!=w2&&w1!=w3&&w1!=w4 && 
						    w2!=w3&&w2!=w4&&w3!=w4 ){
						   	
						   	//-----------------------------
							for(ll c1=1;c1<=4;c1++){
								for(ll c2=1;c2<=4;c2++){
									for(ll c3=1;c3<=4;c3++){
									
										zxy[w1]=v[1]; zxy[w2]=v[2];
										zxy[w3]=v[3]; zxy[w4]=v[4];
										
										ll f1=mest(zxy[1],c1,zxy[2]); 
										ll f2=mest(f1,c2,zxy[3]);   
										ll f3=mest(f2,c3,zxy[4]);     
										if(f3>=0&&f3<=24&&f1!=-817&&f2!=-817&&f3!=-817) {
											ll p1=0;k++;
											zl[k][++p1]='(';zl[k][++p1]='(';zl[k][++p1]='(';
											if(zxy[1]>=10) zl[k][++p1]='1';zl[k][++p1]=char(zxy[1]%10+'0');
											zl[k][++p1]=upp[c1];
											if(zxy[2]>=10) zl[k][++p1]='1';zl[k][++p1]=char(zxy[2]%10+'0');
											zl[k][++p1]=')';   zl[k][++p1]=upp[c2];
											if(zxy[3]>=10) zl[k][++p1]='1';zl[k][++p1]=char(zxy[3]%10+'0');
											zl[k][++p1]=')';   zl[k][++p1]=upp[c3];
											if(zxy[4]>=10) zl[k][++p1]='1';zl[k][++p1]=char(zxy[4]%10+'0');
											zl[k][++p1]=')';
											p_zl[k]=f3;
										}
										
										ll g1=mest(zxy[2],c2,zxy[3]); 
										ll g2=mest(zxy[1],c1,g1);      
										ll g3=mest(g2,c3,zxy[4]);  
										if(g3>=0&&g3<=24&&g1!=-817&&g2!=-817&&g3!=-817){
											ll p2=0;k++;
											zl[k][++p2]='(';zl[k][++p2]='(';
											if(zxy[1]>=10) zl[k][++p2]='1';zl[k][++p2]=char(zxy[1]%10+'0');
											zl[k][++p2]=upp[c1]; zl[k][++p2]='(';
											if(zxy[2]>=10) zl[k][++p2]='1';zl[k][++p2]=char(zxy[2]%10+'0');
											zl[k][++p2]=upp[c2];
											if(zxy[3]>=10) zl[k][++p2]='1';zl[k][++p2]=char(zxy[3]%10+'0');
											zl[k][++p2]=')';  zl[k][++p2]=')'; zl[k][++p2]=upp[c2];
											if(zxy[4]>=10) zl[k][++p2]='1';zl[k][++p2]=char(zxy[4]%10+'0');
											zl[k][++p2]=')';
											p_zl[k]=g3;
										}
										
										ll h1=mest(zxy[3],c3,zxy[4]);  
										ll h2=mest(zxy[2],c2,h1);     
										ll h3=mest(zxy[1],c1,h2);   
										if(h3>=0&&h3<=24&&h1!=-817&&h2!=-817&&h3!=-817){
											ll p3=0;++k;
											zl[k][++p3]='(';
											if(zxy[1]>=10) zl[k][++p3]='1';zl[k][++p3]=char(zxy[1]%10+'0');
											zl[k][++p3]=upp[c1]; zl[k][++p3]='(';
											if(zxy[2]>=10) zl[k][++p3]='1';zl[k][++p3]=char(zxy[2]%10+'0');
											zl[k][++p3]=upp[c2]; zl[k][++p3]='(';
											if(zxy[3]>=10) zl[k][++p3]='1';zl[k][++p3]=char(zxy[3]%10+'0');
											 zl[k][++p3]=upp[c2];
											if(zxy[4]>=10) zl[k][++p3]='1';zl[k][++p3]=char(zxy[4]%10+'0');
											zl[k][++p3]=')';zl[k][++p3]=')';  zl[k][++p3]=')';
											p_zl[k]=h3;
										}
										
										ll a1=mest(zxy[1],c1,zxy[2]); 
										ll a2=mest(zxy[3],c3,zxy[4]); 
										ll a3=mest(a1,c2,a2);      	
										if(a3>=0&&a3<=24&&a1!=-817&&a2!=-817&&a3!=-817){
											ll p4=0;++k;
											zl[k][++p4]='(';zl[k][++p4]='(';
											if(zxy[1]>=10) zl[k][++p4]='1';zl[k][++p4]=char(zxy[1]%10+'0');
											zl[k][++p4]=upp[c1]; 
											if(zxy[2]>=10) zl[k][++p4]='1';zl[k][++p4]=char(zxy[2]%10+'0');
											zl[k][++p4]=')'; zl[k][++p4]=upp[c2]; zl[k][++p4]='(';
											if(zxy[3]>=10) zl[k][++p4]='1';zl[k][++p4]=char(zxy[3]%10+'0');
											zl[k][++p4]=upp[c3];
											if(zxy[4]>=10) zl[k][++p4]='1';zl[k][++p4]=char(zxy[4]%10+'0');
											zl[k][++p4]=')';zl[k][++p4]=')'; 
											p_zl[k]=a3;
										}
										
										ll b1=mest(zxy[2],c2,zxy[3]);  
										ll b2=mest(b1,c3,zxy[4]);      
										ll b3=mest(zxy[1],c1,b2);    
										if(b3>=0&&b3<=24&&b1!=-817&&b2!=-817&&b3!=-817){
											ll p5=0;++k;
											zl[k][++p5]='(';
											if(zxy[1]>=10) zl[k][++p5]='1';zl[k][++p5]=char(zxy[1]%10+'0');
											zl[k][++p5]=upp[c1]; zl[k][++p5]='(';zl[k][++p5]='(';
											if(zxy[2]>=10) zl[k][++p5]='1';zl[k][++p5]=char(zxy[2]%10+'0');
											zl[k][++p5]=upp[c2];
											if(zxy[3]>=10) zl[k][++p5]='1';zl[k][++p5]=char(zxy[3]%10+'0');
											zl[k][++p5]=')';  zl[k][++p5]=upp[c3];
											if(zxy[4]>=10) zl[k][++p5]='1';zl[k][++p5]=char(zxy[4]%10+'0');
											zl[k][++p5]=')';zl[k][++p5]=')';
											p_zl[k]=b3;
										}
										
									}
								}
							}
						   	//-----------------------------
						   	
						}
					}
				}
			}
		}
		ll ans=0;
		for(ll i=1;i<=k;i++) ans=max(ans,p_zl[i]);
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：andyli (赞：1)

枚举全排列后分两类，一类形如 `a[0] op a[1] op a[2] op a[3]`，另一类形如 `(a[0] op a[1]) op (a[2] op a[3])`，枚举符号，检查是否为整数并更新答案。

```cpp
int main() {
    multipleTests([&] {
        dRV(int, a, 4);

        auto op = [&](int tp, auto& x, auto y) {
            switch (tp) {
            case 0:
                x += y;
                break;
            case 1:
                x -= y;
                break;
            case 2:
                x *= y;
                break;
            case 3:
                x /= y;
                break;
            }
        };
        int ans = 0;
        auto update = [&](ld x) {
            if (std::fabs(x - std::round(x)) < 1e-9) {
                int t = std::round(x);
                if (t <= 24)
                    chkmax(ans, t);
            }
        };
        sort(a);
        do
            _for (i, 4)
                _for (j, 4)
                    _for (k, 4) {
                        ld t = a[0];
                        op(i, t, a[1]);
                        op(j, t, a[2]);
                        op(k, t, a[3]);
                        update(t);
                        t = a[0];
                        op(i, t, a[1]);
                        ld t2 = a[2];
                        op(j, t2, a[3]);
                        op(k, t, t2);
                        update(t);
                    }

        while (next_permutation(a).found);
        print(ans);
    });
    return 0;
}
```

---

## 作者：xiangyanhao (赞：0)

本题数据规模很小，只需要用 `multiset` 实现每次取出两个数（并删除），算完之后放回即可。由于数据规模很小，基本无需考虑代码的常数问题。核心代码如下：

```cpp
int ans;
void dfs(multiset<double> s){ //s储存题目中给出的四个数
	if(ans==24) return;
	if(s.size()==1){
		if(int(*s.begin())==*s.begin()&&*s.begin()<=24)
			ans = max(ans,int(*s.begin())); //满足条件，更新答案
		return;
	}
	vector<double> vec; //使用vector作为临时容器，用来处理数的删除
	multiset<double> tmp;
	for(int i = 0;i < s.size();i++){
		for(int j = 0;j < s.size();j++){
			if(i==j) continue;
			double u,v; //u、v存储被删除的两个数的值
			vec.clear();
			tmp.clear();
			int k = 0;
			for(double a:s){
				if(k!=i&&k!=j){
					vec.push_back(a);
				}
				if(k==i) u = a; 
				if(k==j) v = a; 
				k++;
			}
			multiset<double> tmp2;
			for(double num:vec){
				tmp.insert(num); //将删除后的数放入tmp多重集中
			}
			//依次枚举每一种运算
			tmp2 = tmp;
			tmp2.insert(u+v);
			dfs(tmp2);
			tmp2 = tmp;
			tmp2.insert(u-v);
			dfs(tmp2);
			tmp2 = tmp;
			tmp2.insert(u*v);
			dfs(tmp2);
			if(v==0) continue;
			tmp2 = tmp;
			tmp2.insert(u/v);
			dfs(tmp2);
		}
	}
}
```

---

