# [ABC332C] T-shirts

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc332/tasks/abc332_c

AtCoder 社は[ロゴ入りの T シャツ](https://suzuri.jp/AtCoder/5510290/t-shirt/s/ash)を販売しています。

高橋君の $ N $ 日間の予定が `0`, `1`, `2` のみからなる長さ $ N $ の文字列 $ S $ で与えられます。  
具体的には、$ 1\leq\ i\leq\ N $ をみたす整数 $ i $ について、

- $ S $ の $ i $ 文字目が `0` のとき、$ i $ 日目に何の予定も入っていません。
- $ S $ の $ i $ 文字目が `1` のとき、$ i $ 日目に高橋君は食事に行く予定があります。
- $ S $ の $ i $ 文字目が `2` のとき、$ i $ 日目に高橋君は競技プログラミングのイベントに行く予定が入っています。

高橋君は無地の T シャツを $ M $ 枚持っており、$ 1 $ 日目の直前の時点ですべて洗濯済みの状態となっています。  
これに加えて、次の条件をみたすように行動できるように、高橋君は AtCoder のロゴ入りの T シャツを何枚か購入する事にしました。

- 食事に行く日には、無地の T シャツ $ 1 $ 枚またはロゴ入りの T シャツ $ 1 $ 枚を着用する。
- 競技プログラミングのイベントに行く日にはロゴ入りの T シャツ $ 1 $ 枚を着用する。
- 何の予定もない日には T シャツを着用しない。加えて、その時点で着用済みの T シャツを全て洗濯する。 洗濯した T シャツは翌日から着用できる。
- 一度着用した T シャツは次に洗濯するまで着用できない。

$ N $ 日間のうち予定が入っている日すべてについて、条件をみたす T シャツを着用できるようにするために、高橋君は最低何枚のTシャツを購入する必要があるか求めてください。 新しく T シャツを購入する必要がないならば $ 0 $ を出力してください。  
ただし、購入した T シャツも $ 1 $ 日目の直前の時点ですべて洗濯済みの状態で存在するものとします。

## 说明/提示

### 制約

- $ 1\leq\ M\leq\ N\leq\ 1000 $
- $ S $ は `0`, `1`, `2` のみからなる長さ $ N $ の文字列
- $ N,M $ は整数

### Sample Explanation 1

高橋君がロゴ入りの T シャツを $ 2 $ 枚購入したとき、次のようにして高橋君は T シャツを着用することができます。 - $ 1 $ 日目、高橋君はロゴ入りの T シャツを着用して食事に行きます。 - $ 2 $ 日目、高橋君は無地の T シャツを着用して食事に行きます。 - $ 3 $ 日目、高橋君はロゴ入りの T シャツを着用して競技プログラミングのイベントに行きます。 - $ 4 $ 日目、高橋君は予定がないため、着用した T シャツをすべて洗濯します。これにより、$ 1,2,3 $ 日目に着用した T シャツを再び着用することが可能になります。 - $ 5 $ 日目、高橋君はロゴ入りの T シャツを着用して競技プログラミングのイベントに行きます。 - $ 6 $ 日目、高橋君はロゴ入りの T シャツを着用して競技プログラミングのイベントに行きます。 高橋君がロゴ入りの T シャツを $ 1 $ 枚以下しか購入しなかった場合には、 どのようにしても条件をみたすように T シャツを着用することができません。 よって、$ 2 $ を出力します。

### Sample Explanation 3

高橋君は新しく T シャツを購入する必要はありません。

## 样例 #1

### 输入

```
6 1
112022```

### 输出

```
2```

## 样例 #2

### 输入

```
3 1
222```

### 输出

```
3```

## 样例 #3

### 输入

```
2 1
01```

### 输出

```
0```

# 题解

## 作者：xxr___ (赞：2)

### 思路：
考虑贪心策略，因为普通的衣服是不用单独购买的，而特殊的衣服需要单独购买，所以每次当 $s_i$ 为 `1` 的时候判断如果普通的件数是否大于 `0` 如果大于 `0` 就说明距离上一次洗衣服还剩下一些普通的衣服，故直接穿普通的衣服就可以了，而如果 $s_i$ 为 `2` 时直接判断是否还有新的特殊衣服，如果有直接穿上并跳过，如果不够了，就说明要再买一件特殊衣服，就让计数器加一。最后如果 $s_i$ 为 `0` 直接把普通衣服恢复至 $M$ 特殊衣服回复到计数器即可。
### 赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m,bt=0,bt2=0;
	cin>>n>>m;
	string s;
	int ft=m;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='0'){
			ft=m;bt=bt2;
		}
		if(s[i]=='1'){
			if(ft>0)ft--;
			else if(ft==0&&bt>0) bt--;
			else if(ft==0&&bt==0) bt2++;
		}
		if(s[i]=='2'){
			if(bt>0)bt--;
			else bt2++;
		}
	}
	cout<<bt2;
	return 0;
}
```
[赛时记录](https://atcoder.jp/contests/abc332/submissions/48372265)

---

## 作者：rainbow_cat (赞：1)

### Part.1 Idea
这里提供一种好理解的二分做法。很明显二分的是印有标志的衣服的数量，重点在于 `check` 函数。对于第 $i$ 天的日程 $c_i$，若 $c_i=0$，将两种衣服的数量补充满，若 $c_i=1$，尽量穿普通衣服，若没有普通衣服，使用特殊衣服，如果连特殊衣服都没有了，返回 $0$。若 $c_i=2$，使用特殊衣服，如果特殊衣服没有了，返回 $0$。最后返回 $1$。  
### Part.2 Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,tmp,l=0,r=1000;
char c[1010];
bool check(int x)
{
	int nnum=m,anum=x;//分别表示普通衣服的数量与特殊衣服的数量
	for(int i=1;i<=n;i++)
	{
		if(c[i]=='0')nnum=m,anum=x;
		if(c[i]=='1')
		{
			if(nnum)nnum--;
			else 
			{
				if(anum)anum--;
				else return 0;
			}
		}
		if(c[i]=='2')
		{
			if(anum)anum--;
			else return 0;
		}
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	tmp=m;
	for(int i=1;i<=n;i++)cin>>c[i];
	while(l<r)//二分
	{
		int mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：lemon_qwq (赞：1)

这题很令人愉悦。

按题意模拟即可，优先级是素色衣服大于 logo 图案衣服，因为 logo 图案衣服你初始没有，要尽量少买衣服。

如果 logo 图案衣服和素色衣服都没有，就买一件 logo 图案衣服。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
string s;
int ss,lo,ans;
int main(){
	cin>>n>>m;
	ss=m;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='0'){//洗干净所有衣服，k 为你买的 logo 图案衣服数量。
			ss=m;
			lo=k;
		}
		else if(s[i]=='2'){//花一件 logo 衣服。
			if(lo-1<0){
				k++;
				ans++;
			}else{
				lo--;
			}
		}else{
			if(ss!=0){//判断有没有素色衣服。
				ss--;
			}else{
				if(lo-1<0){//两种衣服都没有干净的了。
					k++,ans++;
				}else{//没有素色衣服但是有 logo 图案衣服。
					lo--;
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

这是一道很简单的题，按题意模拟即可。

本题有一点贪心的思想，如果是吃饭，就要优先选择普通的衣服，普通的衣服用完了以后再买带 logo 的。

注意：当某天没有日程的时候就要把累计 logo 服装的数量取最大值，然后清零。

示例代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,m,logo=0,normal=0,ans=0;//计数器，记录服装数量
	string s;
	cin>>n>>m;
	cin>>s;
	for(int i=0;i<n;++i){
		if(s[i]=='0'){
			ans=max(ans,logo);
			logo=0,normal=0;
		}
		else if(s[i]=='1'){
			if(normal!=m){//优先选择普通的衣服
				++normal;
			}else{//普通的衣服用完了以后再买带 logo 的
				++logo;
			}
		}else{
			++logo;
		}
	}ans=max(ans,logo);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：indream (赞：0)

## \[ABC332C] T-shirts 题解
[AC](https://atcoder.jp/contests/abc332/submissions/48386339)

模拟贪心即可。~~C 竟然那么简单~~

贪心思路：先穿原有的，实在不够就买新的。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cm,dm,a,ca,da;
//cm:clean m;dm:dirty m;a:atcoder;etc.
char s[1005];
int main(){
  scanf("%d %d\n%s",&n,&m,s);
  cm=m;dm=0;
  a=0;ca=0;da=0;
  for(int i=0;i<n;++i){
    switch(s[i]){
      case '0':
        cm=m;dm=0;
        ca=a;da=0;//模拟洗干净衣服
        break;
      case '1':
        if(cm>0){
          --cm;++dm;//穿原有
        }else if(ca>0){
          --ca;++da;
        }else{
          ++a;da++;
        }
        break;
      case '2':
        if(ca>0){
          --ca;++da;//穿买的
        }else{
          ++a;++da;//买，并把它弄脏
        }
        break;
    }
  }
  printf("%d",a);
  return 0;
}
```

---

## 作者：xu222ux (赞：0)

# [洛谷ABC332C](https://www.luogu.com.cn/problem/AT_abc332_c)
# [原题](https://atcoder.jp/contests/abc332/tasks/abc332_c)

## 思路

会发现只需要线性的扫一遍就可以。

最简单的，今天没事情干，我们就可以把所有衣服全洗了，相当于恢复了初始状态。而今天如果去吃饭，那么今天就有两种衣服可以穿，如果都没得穿了，就再多买一件衣服。最后要是今天打比赛，就只能穿比赛服了，没有就再买一件。

时间复杂度 $O(N)$。

不明白的看代码。

## code
```cpp
#include<bits/stdc++.h>
using namespace std; 
#define int long long//“好习惯”
int n,x,y,ansx,ansy;
int a[1003];
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		char in;cin>>in;
		a[i]=in-'0';
	}
	ansx=x,ansy=0;
	for(int i=1;i<=n;i++){
		if(a[i]==0){//没事干
			ansx=x,ansy=y;//洗衣服
		}else if(a[i]==1){
			if(ansy==0&&ansx==0)y++;//没得穿就买
			else if(ansy==0)ansx--;
			else if(ansx==0)ansy--;
			else ansx--;
		}else{
			if(ansy==0)y++;
			else ansy--;//没得穿就买
		}
	} 
	cout<<y;//输出答案
	return 0;
}

```

---

## 作者：FinderHT (赞：0)

### 思路

可以看到数据范围不是很大，所以我们直接枚举要买的带有徽标的衬衫件数即可。设目前可以穿的普通衬衫的件数为 $x$，目前可以穿的带有徽标的衬衫件数为 $y$，每次枚举分别初始化为 $m$ 和现在枚举到的数。

接下来我们遍历输入的字符串，判断枚举到的值是否行得通。

- 这天的日程安排为空闲：可以将 $x$ 和 $y$ 重置为本次枚举的初始值（$m$ 和枚举到的数）。
- 这天的日程安排为出去吃饭：如果 $x>0$，那么把 $x$ 的值减 $1$；如果 $x\le 0,y>0$，那么把 $y$ 的值减 $1$。否则说明本次枚举到的值是错误的，跳出判断即可。
- 这天的日程安排为参加编程竞赛：如果 $y>0$，那么把 $y$ 的值减 $1$。否则说明本次枚举到的值是错误的，跳出判断。

如果某一次在整个过程中没有跳出判断，说明此次枚举到的数就是至少需要购买衬衫的件数，终止枚举，输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
    int n,m;
    string s;
    cin>>n>>m>>s;
    int i=0;
    while(true){
        int x=m,y=i;//x,y为思路中所述的变量，每次都要初始化
        bool flag=true;
        for(int j=0;j<n;j++){
            if(s[j]=='0')x=m,y=i;//重置成本次枚举的初始值
            else if(s[j]=='1'){
                if(x>0)
                    x--;
                else if(y>0&&x<=0){
                    y--;
                }
                else{//跳出判断
                    flag=false;
                    break;
                }
            }
            else if(s[j]=='2'){
                if(y>0)
                    y--;
                else{//跳出判断
                    flag=false;
                    break;
                }
            }
        }
        if(flag){//如果符合要求
            cout<<i;
            return 0;
        }
        i++;//继续枚举
    }
    return 0;
}
```

---

## 作者：tder (赞：0)

场上死磕线性没磕出来，提供一种别样的思路。

---

小 T 想有一个长达 $n$ 天的出行计划，每天的计划是吃饭、比赛或是休息：

- 吃饭时，需要穿一件 $A$ 衣服或是一件 $B$ 衣服；
- 比赛时，需要穿一件 $B$ 衣服；
- 休息时，清洗所有已穿过的衣服。

特别地，一件衣服在清洗之前只能穿一次。

小 T 有 $m$ 件 $A$ 衣服，求他最少需要多少件 $B$ 衣服。

---

由于每天最多只穿一件 $B$ 衣服，$n$ 天中最多穿 $n$ 件 $B$ 衣服。令小 T 最少需要 $k$ 件 $B$ 衣服，显然有 $0\le k\le n$，二分答案即可。

检验当有 $k$ 件 $B$ 衣服时能否够穿时，考虑分别用 $a,b$ 表示当前还可穿的 $A,B$ 衣服的数量，那么：

- 吃饭时，优先穿 $A$ 衣服，此时 $a\leftarrow a-1$。若无 $A$ 衣服即 $a=0$ 时穿一件 $B$ 衣服，$b\leftarrow b-1$。若没有任何衣服可穿即 $a=b=0$ 时，显然不够穿；
- 比赛时，穿一件 $B$ 衣服，此时 $b\leftarrow b-1$。若无 $B$ 衣服即 $b=0$ 时则不够穿；
- 休息时，将所有衣服清洗，此时 $a\leftarrow m,b\leftarrow k$。

时间复杂度 $O(n\log n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
string s;
bool check(int k) {
	int a = m, b = k;
	for(char c : s) {
		if(c == '1') { // 吃饭
			if(a) a--;
			else if(b) b--;
			else return 0;
		} else if(c == '2') { // 比赛
			if(b) b--;
			else return 0; 
		} else { // 休息
			a = m;
			b = k;
		}
	} 
	return 1;
}
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m>>s;
	int l = 0, r = n; 
	while(l < r) { // 二分答案
		int k = (l + r) / 2; // 中间值
		if(check(k)) { // 当前够穿寻找更小的 k
			r = k;
		} else { // 当前不够穿则寻找够穿的 k
			l = k + 1;
		}
	}
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc332_c 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc332/tasks/abc332_c)

[Luogu](https://www.luogu.com.cn/problem/AT_abc332_c)

### 简要题意

高桥公司有一个 $n$ 天的行程 $s$，在初始时，他们有 $m$ 件普通衣服。

每天的活动情况为：

如果 $s_i$ 为 `0`，那么这一天没有任何安排，可以将之前所有的普通衣服和徽标衣服洗干净；

如果 $s_i$ 为 `1`，那么这一天要身穿普通或徽标衣服；

如果 $s_i$ 为 `2`，那么这一天要身穿徽标衣服。

注：每件普通衣服和徽标衣服在洗干净之前只能穿一天。

问至少要买多少件衣服才能使每天都有衣服穿。

### 简要思路

二分答案，寻找最小的购买的衣服数量。

因为徽标衣服是相对“万能”的，所以我们只需二分徽标衣服的数量。

在 `check` 判断中，如果能穿普通衣服就先穿普通衣服，否则穿徽标衣服。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int n,m;
char s[1005];

bool check(int x){
	int num1=m;//普通衣服的数量
	int num2=x;//徽标衣服的数量
	for(int i=1;i<=n;i++){
		if(s[i]=='0'){//无安排
			num1=m;
			num2=x;//将前面所有穿过的衣服洗干净
		}else if(s[i]=='1'){
			if(num1>0)num1--;//能穿普通衣服先穿普通衣服
			else{
				if(num2>0)num2--;
				else return false;
			}
		}else{
			if(num2>0)num2--;//只能穿徽标衣服
			else return false;
		}
	}
	return true;
}

signed main(){
	std::cin>>n>>m>>s+1;
	
	int l=0,r=1000;
	while(l<=r){//二分答案
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	std::cout<<r+1<<endl;
	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc332/submissions/48429908)

[Luogu](https://www.luogu.com.cn/record/139244151)

**THE END.**

**THANK YOU.**

---

## 作者：xixiangrui (赞：0)

### 题面概况：
现在有两种衣服，普通衣服和特殊衣服，而商店中卖普通衣服，你已经有 $M$ 件普通衣服。现在给定一个长度为 $N$ 的字符串 $S$ 每一个字符 $s_i$ 都表示的每一天的一个状态，求最少需要购买几件特殊的衣服，有以下几种情况：
- 如果 $s_i$ 为 `0` 则在这一天你会进行洗衣服，即把以前所有的普通衣服和你买的衣服都洗了。
- 如果 $s_i$ 为 `1` 则在这一天你可以穿普通的衣服或特殊的衣服。
- 如果 $s_i$ 为 `2` 则在这一天你只能穿特殊的衣服。

### 思路分析：
不难想到我们可以用两个变量来记录当前可以有几件普通衣服和特殊衣服可以穿。
##### 则可以分以下三种情况讨论：
1. 若 $s_i$ 为 `0` 则将表示普通衣服的初始化到 $M$ 将表示特殊衣服的初始化到目前为止需要购买的特殊衣服的件数。
2. 若 $s_i$ 为 `1` 则考虑贪心，既然题目让我们求购买最少的特殊衣服的件数，那不就是尽可能的让普通的衣服数量更多吗，所以我们考虑如果此时剩余普通衣服的数量够，那么直接穿普通衣服，否则如果特殊衣服的件数够就穿特殊衣服，否则购买特殊衣服。
3. 若 $s_i$ 为 `2` 则判断如果此时特殊衣服的件数够，直接穿上，否则买一个即可。

### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[2005]; 
int main(){
	int n,m,flag=0,flag2=0;
	cin>>n>>m;
	int ft=m;
	for(int i=0;i<n;i++){
		cin>>s[i];
	}
	for(int i=0;i<n;i++){
		if(s[i]=='0'){
			ft=m;flag=flag2;
		}
		if(s[i]=='1'){
			if(ft>0)ft--;
			else if(ft==0&&flag>0) flag--;
			else if(ft==0&&flag==0) flag2++;
		}
		if(s[i]=='2'){
			if(flag>0)flag--;
			else flag2++;
		}
	}
	cout<<flag2;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc332_c)

## 思路

二分答案。

读入数据后从 $0$ 到 $N$ 二分，每次二分的是要买的带有 AtCoder 标志衣服的数量。

检查这种方案是否能行时我们可以用两个“已使用”标记分别模拟。

当模拟到第 $i$ 天（$1\le i\le N$）时：

1. 这一位为 `0`：将普通衣服和带有 AtCoder 标志衣服的“已使用”标记清空，即为清洗衣物。

1. 这一位为 `1`：优先选择普通衣服来穿，并将普通衣服的“已使用”标记 $+1$。如果普通衣服的“已使用”标记等于 $M$（也就是普通衣服穿完了），那么就选择带有 AtCoder 标志衣服来穿，将其“已使用”标记 $+1$。

1. 这一位为 `2`：选择带有 AtCoder 标志衣服来穿，将其“已使用”标记 $+1$。

- 当带有 AtCoder 标志衣服的“已使用”标记超出了当前所买的带有 AtCoder 标志衣服的数量时，说明这种方案行不通。当模拟完成后仍旧没有跳出函数，那么就说明这种方案行得通。


## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline char readc(){//字符快读。
	char c=getchar();
	while(c==' '||c=='\n'||c=='\r')c=getchar();
	return c;
}
const int N=1010;
int n,m,ans;
char c[N];
inline bool check(int x){
	int cnt=0,cntt=0;
	for(int i=1;i<=n;++i){
		if(c[i]=='0')cnt=cntt=0;
		else if(c[i]=='1'){
			if(cntt<m)++cntt;
			else ++cnt;
			if(cnt>x)return 0;
		}
		else{
			++cnt;
			if(cnt>x)return 0;
		}
	}
	return 1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)c[i]=readc();
	int l=0,r=n;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/139167207)

---

## 作者：FreedomKing (赞：0)

简单模拟题，根据题意模拟就能通过。

### 思路

因为出去吃饭可以穿普通衬衫**或** logo 衬衫，而参加编程活动**只能**穿 logo 衬衫，所以考虑在吃饭时优先穿普通衬衫。

记 $x$ 为连续出去的几天内吃饭需要穿的衬衫总数，$M$ 为普通衬衫数，易得 $\max(0,x-M)$ 即为需要穿的 logo 衬衫数；记 $x_1$ 为连续出去的几天内参加编程活动需要穿的 logo 衬衫总数。每次遇到没有活动的某天就对两个计数器清零代表洗衬衫，否则就用两者的和更新答案，即 $ans=\max(ans,\max(0,x-M)+x_1)$。

剩下的见注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5;
const int mod=1e9+7,mmod=1e7+7,Lmod=998244353;
int a[N],b[N],f[mN][mN],n,m,t,k,ans;
vector<int>e[N];
bool vis[N];
string s;
inline int qread(){
#define qr qread()
	int x1=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		t^=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x1=(x1<<3)+(x1<<1)+c-'0';
		c=getchar();
	}
	return (t?x1:-x1);
}
inline int qpow(int x1,int p,int mod){
	mod=(mod?mod:LONG_LONG_MAX);
	x1=(p?x1:1);
	x1%=mod;
	int t=1;
	while(p>1){
		if(p&1) t=(t*x1)%mod;
		x1=(x1*x1)%mod;
		p>>=1;
	}
	return (t*x1)%mod;
}
inline void qwrite(int x1){
#define qw(_) qwrite(_)
#define qwe(_) qw(_),putchar('\n')
	if(x1<0) x1=-x1,putchar('-');
	if(x1>9) qwrite(x1/10);
	putchar(x1%10+'0');
}
signed main(){
	cin>>n>>m>>s;
	int x1=0,x=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='2') x1++;
		//如果是编程活动，必须穿 logo 衬衫
		else if(s[i]=='1') x++;
		//吃饭，先记个数再决定穿 logo 衬衫的天数
		else{
			//如果今天没有场合了，统计一下需要穿的 logo 衬衫并更新答案
			ans=max(ans,x1+max(0ll,x-m));
			x=0;
			x1=0;
		}
	}
	ans=max(ans,x1+(x>m?x-m:0));
	//输入不一定以休息日结束，所以最后必须再更新一次答案
	cout<<ans;
	return 0;
}
```

---

## 作者：sfqxx1 (赞：0)

## 思路

- 如果 `d` 是 `0`，代表那天没有计划，所有穿过的 T 恤都会被洗干净。因此，`p`（普通 T 恤数量）重置为 `M`，`l`（标志 T 恤数量）设置为 `b`（已购买的标志 T 恤数量）。

- 如果 `d` 是 `1`，Takahashi 可以穿普通 T 恤或标志 T 恤。优先穿普通 T 恤（如果有的话），否则穿标志 T 恤。如果两者都没有，需要购买一件新的标志 T 恤。

- 如果 `d` 是 `2`，Takahashi 必须穿标志 T 恤。如果没有可用的标志 T 恤，他需要购买一件新的。
   
##  代码
```

N, M=map(int,input().split())

s = input()

p = M

l = 0

b = 0

for d in s:

    if d == '0':

        p = M

        l = b

    elif d == '1':

        if p > 0:

            p -= 1

        elif l > 0:

            l -= 1

        else:

            b += 1

    elif d == '2':

        if l > 0:

            l -= 1

        else:

            b += 1

print(b)
```

---

## 作者：yhx0322 (赞：0)

## Description
给你一个长度为 $N$ 的字符串 $S$，由字符 `0`、`1` 和 `2` 组成。

并且在有 $M$ 件素色的 T 恤，在第一天的时候就已经洗好了。

对于字符串 $S$ 的每一个位置 $S_i$:
- 如果 $S_i$ 为字符 `0`，代表这一天没有安排，并且会把所有衣服清洗干净。
- 如果 $S_i$ 为字符 `1`，代表计划在这一天出去吃饭，会穿一件素色 T 恤或者格子 T 恤。
- 如果 $S_i$ 为字符 `2`，代表计划在这一天参加编程活动，只能穿格子 T 恤。

现在求：至少需要再购买几件 T 恤才能满足要求。

## Solution
这里提供一种二分的做法。

二分最少再用几件 T 恤，每次检验就扫一遍字符串，记录两个变量 $p$ 和 $l$，分别表示素色和格子 T 恤还剩多少件。每次选择合适的衣服，如果没有了就返回假，最后返回真即可。

答案为左边界。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;
char s[N];
int n , m ;
bool check(int mid) {
	int p = n , l = mid ;
	for(int i = 1 ; i <= m ; i++) {
		if(s[i] == '0') {
			p = n , l = mid ;
		}
		else if(s[i] == '1') {
			if(!p && !l) return false ;
			if(!p) l-- ;
			else p-- ;
		}
		else {
			if(!l) return false ;
			l--;
		}
	}
	return true ;
}
signed main() {
	scanf("%d%d\n%s\n" , &m , &n , s + 1) ;
	int l = 0, r = m;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid - 1 ;
		else l = mid + 1 ;
	}
	printf("%d", l) ;
	return 0 ;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

我们可以将整个字符串用 `0` 分割成很多个部分。对于每个部分，我们统计 `1` 和 `2` 的个数，对于 `2`，我们显然要买衣服；对于 `1`，我们需要看看原来有的衣服够不够用，差多少件卖多少件。然后对每个部分需要的衣服取个最大值即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	ll n, m, ans = 0;
	cin >> n >> m;
	string s;
	cin >> s;
	if (s[(ll)s.size() - 1] != '0') {
		s += '0';
	} 
	ll cnt1 = 0;
	ll cnt2 = 0;
	for (ll i = 0; i < (ll)s.size(); i++) {
		if (s[i] == '1') {
			cnt1++;
		}
		if (s[i] == '2') {
			cnt2++;
		}
		if (s[i] == '0') {
			ll ne = cnt2;
			if (cnt1 > m) {
				ne += cnt1 - m;
			}
			ans = max(ans, ne);
			cnt1 = 0;
			cnt2 = 0;
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：Phartial (赞：0)

我们贪心的处理每一天，并维护目前需要的普通衬衫和文化衫的数量 $v_n,v_l$：

- 如果 $S_i=\texttt{0}$，则我们必然会清洗所有普通衬衫和文化衫，即令 $v_n\gets 0$，$v_l\gets 0$；
- 如果 $S_i=\texttt{1}$，则我们必然会采取这样一种贪心策略：如果还有普通衬衫穿就优先穿普通衬衫，否则穿文化衫。即，若 $v_n<M$，就令 $v_n\gets v_n+1$，否则令 $v_l\gets v_l+1$；
- 如果 $S_i=\texttt{2}$，则我们只能穿文化衫，令 $v_l\gets v_l+1$ 即可。

最后，统计 $N$ 天里最大的 $v_l$ 即可。

```cpp
#include <iostream>

using namespace std;

int n, m, vn, vl, ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    char ch;
    cin >> ch;
    if (ch == '0') {
      vn = vl = 0;
    } else if (ch == '1') {
      if (vn < m) {
        ++vn;
      } else {
        ++vl;
      }
    } else {
      ++vl;
    }
    ans = max(ans, vl);
  }
  cout << ans;
  return 0;
}
```

---

