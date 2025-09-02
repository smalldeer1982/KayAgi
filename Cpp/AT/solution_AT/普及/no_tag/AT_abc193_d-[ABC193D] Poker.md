# [ABC193D] Poker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc193/tasks/abc193_d

$ 1,\ 2,\ \dots,\ 9 $ が表に書かれたカードが $ K $ 枚ずつ、計 $ 9K $ 枚のカードがあります。  
 これらのカードをランダムにシャッフルして、高橋くんと青木くんにそれぞれ、$ 4 $ 枚を表向きに、$ 1 $ 枚を裏向きにして配りました。  
 高橋くんに配られたカードが文字列 $ S $ として、青木くんに配られたカードが文字列 $ T $ として与えられます。  
 $ S,\ T $ は $ 5 $ 文字の文字列で、先頭 $ 4 $ 文字は `1`, `2`, $ \dots $, `9` からなり、表向きのカードに書かれた数を表します。 末尾 $ 1 $ 文字は `#` であり、裏向きのカードであることを表します。  
 $ 5 $ 枚の手札の点数を、$ c_i $ をその手札に含まれる $ i $ の枚数として、$ \displaystyle\ \sum_{i=1}^9\ i\ \times\ 10^{c_i} $ で定義します。  
 高橋くんが青木くんより点数の高い手札を持っていたら高橋くんの勝ちです。  
 高橋くんの勝つ確率を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ = K\ <\ =\ 10^5 $
- $ |S|\ =\ |T|\ =\ 5 $
- $ S,\ T $ の $ 1 $ 文字目から $ 4 $ 文字目は `1`, `2`, $ \dots $, `9` のいずれか
- `1`, `2`, $ \dots $, `9` はそれぞれ、$ S $ と $ T $ に合計 $ K $ 回までしか出現しない
- $ S,\ T $ の $ 5 $ 文字目は `#`

### Sample Explanation 1

例えば、高橋くんの手札が `11449` 、青木くんの手札が `22338` の場合、高橋くんの点数は $ 100+2+3+400+5+6+7+8+90=621 $ 、青木くんの点数は $ 1+200+300+4+5+6+7+80+9=612 $ で、高橋くんの勝ちになります。 裏向きのカードの大小によって勝敗が決まるので、高橋くんの勝つ確率は $ \frac49 $ です。

### Sample Explanation 3

高橋くんの手札が `11222` 、青木くんの手札が `22281` の場合にのみ高橋くんの勝ちになります。 高橋くんの勝つ確率は $ \frac2{1035} $ です。

## 样例 #1

### 输入

```
2
1144#
2233#```

### 输出

```
0.4444444444444444```

## 样例 #2

### 输入

```
2
9988#
1122#```

### 输出

```
1.0```

## 样例 #3

### 输入

```
6
1122#
2228#```

### 输出

```
0.001932367149758454```

## 样例 #4

### 输入

```
100000
3226#
3597#```

### 输出

```
0.6296297942426154```

# 题解

## 作者：fengenrong (赞：5)

我们不难发现，他们选的五个数必定会有一个是 `#`，未知的。我们只用枚举高桥和青木两人未知的数的值，再来判断高桥是否能赢就行了。

我们用 $sum_{all}$ 来表示他们两人未知的数一共的可能选法，用 $sum_{win}$ 来表示高桥在其中获胜的数量，则答案就是 $\frac{sum_{win}}{sum_{all}}$。我们可以先用 $sum_t$ 来表示高桥除了未知数的得分，也就是 $\sum_{i=1}^9 i \times 10^{c_i}$，其中 $c_i$ 是数字为 $i$ 高桥的牌的数量，$sum_s$ 表示青木的得分，求法和高桥的一样。对于每一个填入未知数的方案，我们判断高桥是否能赢，如果能赢，将 $sum_{win}$ 自增。而 $sum_{all}$ 是等于 $(k\times 9-8)\times (k\times 9-9)$，其实就是利用到了组合数学。$k\times 9$ 是一共拥有的牌的数量，减去已经使用的八张，高桥的选法就是 $k\times 9-8$。青木的就刚好是高桥的减去一，既为 $k\times 9-9$。最后相乘就可以求出 $sum_{all}$。

### 代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int k;
string s, t;
int bjs[1005], bjt[1005];//分别表示高桥与青木使用第i种牌的数量
int sums, sumt;
signed main() {
    cin >> k;
    cin >> s >> t;
    for (int i = 0; i <= 4; i++) {
        if (s[i] != '#') {
            bjs[s[i] - '0']++;//让高桥的第s[i]种牌的数量增加
        }
        if (t[i] != '#') {
            bjt[t[i] - '0']++;//让青木的第t[i]种牌的数量增加
        }
    }
    for (int i = 1; i <= 9; i++) {
        sums += i * pow(10, bjs[i]);//求出高桥的除了未知数的得分
        sumt += i * pow(10, bjt[i]);//求出青木的除了未知数的得分
    }
    int sum = (k * 9 - 8) * (k * 9 - 9);//求总数
    int ans = 0;
    for (int i = 1; i <= 9; i++) {
        if (bjs[i] + bjt[i] + 1 > k) {//判断是否能选
            continue;
        }
        int op = sums + 9 * i * pow(10, bjs[i]);//算出新的分数
        bjs[i]++;
        for (int j = 1; j <= 9; j++) {
            if (bjs[j] + bjt[j] + 1 > k) {/判断是否能选
                continue;
            }
            int po = sumt + 9 * j * pow(10, bjt[j]);//算出新的分数
            if (op > po) {//合法
                ans += (k - bjs[i] - bjt[i] + 1) * (k - bjt[j] - bjs[j]);//将统计增加
            }
        }
        bjs[i]--;
    }
    printf("%.8lf\n", ans * 1.0 / sum);//输出答案
    return 0;
}
```

---

## 作者：DashZhanghanxu (赞：0)

# 解析
先读取输入值，包括每种数字卡片的数量 $K$，以及高桥和青木手中正面朝上的卡片表示的字符串 $S$ 和 $T$。

然后计算高桥和青木手中已知卡片（前四张）中每个数字（1 到 9）的出现次数。
    
接着预计算 $1$ 到 $10^5$ 的值，以便高效计算分数。

随后遍历所有可能的隐藏卡片组合（高桥的隐藏卡片和青木的隐藏卡片），检查这些组合是否有效。有效组合的条件是：在考虑已知卡片后，剩余的卡片数量足够。

最后对于每一对有效的隐藏卡片组合，分别计算高桥和青木的分数。统计高桥的分数高于青木的有利结果数量。通过将有利结果的数量除以所有有效结果的总数，计算高桥获胜的概率。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int K;string S,T;cin>>K>>S>>T;
    vector<int> sv(10,0),tv(10,0);
    for(int i=0;i<4;++i){sv[S[i]-'0']++;tv[T[i]-'0']++;}
    vector<int> cur(10,0);
    for(int i=1;i<=9;++i){cur[i]=sv[i]+tv[i];}
    long long pow[6];
    pow[0]=1;
    for(int i=1;i<=5;++i){pow[i]=pow[i-1]*10;}
    long long ans=0,d=0;
    for(int j=1;j<=9;++j){
        for(int k=1;k<=9;++k){
            bool flag=true;
            for(int i=1;i<=9;++i){
                int cnt=(j==i)+(k==i);
                if(cur[i]+cnt>K){flag=false;break;}
            }
            if(!flag)continue;
            int rj=K-cur[j];int rk=K-cur[k];
            long long ways=0;
            if(j!=k){ways=(long long)rj*rk;}
            else{ways=(long long)rj*(rj-1);}
            long long point_j=0;
            for(int i=1;i<=9;++i){
                int cnt=sv[i]+(j==i);
                point_j+=i*pow[cnt];
            }
            long long point_k=0;
            for(int i=1;i<=9;++i){
                int cnt=tv[i]+(k==i);
                point_k+=i*pow[cnt];
            }
            if(point_j>point_k){ans+=ways;}
            d+=ways;
        }
    }
    cout<<fixed<<setprecision(15)<<static_cast<double>(ans)/d<<endl;
    return 0;
}
```

---

## 作者：_Flora_ (赞：0)

## 题意

有 $1\sim9$ 的牌各 $K$ 张，每人分 $5$ 张。

得分规则是 $\displaystyle \sum_{i=1}^9 i \times 10^{c_i}$，其中 $C_i$ 是这个人有牌 $i$ 的张数。

当每人发了 $4$ 张牌时，问第一个人获胜的概率。

## 解析

对于每一对 $(x,y)$，Takahashi 有卡牌 $x$ 且 Aoki 有卡牌 $y$ 的总组合数为：

$\begin{cases}C_xC_y&{(x≠y)}\\C_x(C_x-1)&{(x=y)}\end{cases}$

接着枚举每一对 $(x,y)$，拿最终的结果除以 $(9K-8)(9K-9)$ 即可。

## 代码

```c
#include<bits/stdc++.h>
using namespace std;

long long solve(int x)
{
	int i,j;
	
	long long a[10],cnt=0,sum=0,num;
	
	while(x!=0)
	{
		a[cnt]=x%10;
		
		x=x/10;
		
		cnt=cnt+1;
	}
	
	for(i=1;i<=9;i++)
	{
		num=i;
		
		for(j=0;j<cnt;j++)
		{
			if(a[j]==i)
			{
				num=num*10;
			}
		}
		
		sum=sum+num;
	}
	
	return sum;
}
int main()
{
	int i,j;
	
	long long n,a,b;
	
	string s1,s2;
	
	double m;
	
	cin>>n>>a>>s1>>b>>s2;
	
	long long c[15],sum=0,x=a,y=b;
	
	for(i=1;i<=9;i++)
	{
		c[i]=n;
	}
	
	while(a>0)
	{
		c[a%10]=c[a%10]-1;
		
		a=a/10;
	}
	
	while(b>0)
	{
		c[b%10]=c[b%10]-1;
		
		b=b/10;
	}
	
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			if(solve(x*10+i)>solve(y*10+j))
			{
				sum=sum+c[i]*(c[j]-(i==j));
			}
		}
	}
	
	m=1.0*sum/((n*9-8)*(n*9-9));
	
	cout<<fixed<<setprecision(9)<<m<<endl;
	return 0;
}
```

---

