# [GCJ 2015 Qualification] Standing Ovation

## 题目描述

今晚是歌剧的首演，你的朋友是女主角（首席女歌手）。你不会在观众席中，但你希望确保她能获得全场起立鼓掌——让每一位观众都站起来为她鼓掌。

最初，所有观众都坐着。每位观众都有一个“害羞等级”。害羞等级为 $S_i$ 的观众会等到至少有 $S_i$ 位其他观众已经站起来鼓掌后，才会立即站起来鼓掌。如果 $S_i = 0$，那么这位观众会无论如何都立刻站起来鼓掌。例如，害羞等级为 $S_i = 2$ 的观众一开始会坐着，只有在看到至少有两个人已经站起来鼓掌后，她才会站起来鼓掌。

你知道所有观众的害羞等级，并且你可以邀请额外的朋友加入观众席，以确保最终所有人都能站起来鼓掌。你可以为这些朋友分配任意害羞等级，不必相同。请问你至少需要邀请多少位朋友，才能保证全场起立鼓掌？

## 说明/提示

**样例解释**

在第 1 组样例中，观众最终会自行完成全场起立鼓掌，无需你邀请任何人——首先害羞等级为 0 的观众会站起来，然后害羞等级为 1 的观众会站起来，依此类推。

在第 2 组样例中，必须邀请一位害羞等级为 0 的朋友，但这样就足以让所有观众都站起来。

在第 3 组样例中，一种最优方案是添加两位害羞等级为 2 的观众。

在第 4 组样例中，只有一位观众，他会立刻站起来。无需邀请任何朋友。

**数据范围**

- $1 \leq T \leq 100$。

**小数据集（7 分）**

- 时间限制：5 秒。
- $0 \leq S_{\text{max}} \leq 6$。

**大数据集（10 分）**

- 时间限制：10 秒。
- $0 \leq S_{\text{max}} \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4 11111
1 09
5 110011
0 1```

### 输出

```
Case #1: 0
Case #2: 1
Case #3: 2
Case #4: 0```

# 题解

## 作者：_Null_Ptr (赞：3)

一道比较不一样的贪心题，题意可以简化为：我们需要保证对于每个害羞等级 $k$，在处理到该等级时，已经站起来的人数至少为 $k$。如果当前起立人数不足，我们就需要添加朋友来补足。

故我们可以从害羞等级 $0$ 开始，逐步处理到最高等级。维护一个当前已起立人数的计数，每当遇到一个等级的观众人数不为 $0$ 时，检查当前起立人数是否足够。如果不足，则添加朋友使其达到当前等级，然后更新起立人数。

具体实现见代码。
```cpp
#include <iostream>
using namespace std;

int T;
void work(int x){
    int n; string s;
    cin >> n >> s;
    int ans = 0;
    int shy = s[0] - '0'; // 初始起立人数为害羞等级0的观众数
    for(int i = 1; i <= n; i++){
        if(s[i] - '0' != 0){ // 如果该等级有观众
            if(shy >= i) // 当前起立人数足够
                shy += (s[i] - '0'); // 更新起立人数
            else{
                ans += (i - shy); // 添加朋友补足到i
                shy = i + (s[i] - '0'); // 更新起立人数
            }
        }
    }
    printf("Case #%d: %d \n", x, ans);
}
int main(){
    cin >> T;
    for (int i = 1; i <= T; i++) work(i);
}
```
~~为什么满分只有 $17$ 分。~~

---

## 作者：Finner_forgeter (赞：2)

# P13211题解

[题目传送门](https://www.luogu.com.cn/problem/P13211)

**题意：**   本题就像一个打怪通关的游戏，打败这个怪可以获得这个怪的战力，但战力不够的时候就只能去提升战力。（~~看视频获得一点战力/充值~~）本题提升战力的方法为“邀请朋友”，怪的战力就是“害羞等级”。

**思路：**   简而言之就是人数够就加上，人数不够就去邀请朋友。（~~打得过就吞噬，打不过就去看视频~~）所以只需要一个 `if(cnt>=i)` 来判断人数够不够让下一个害羞等级的人站起来就行了。

代码实现：

```cpp
#include <bits/stdc++.h>
#define finner_forgeter return
#define love 0
#define KamisatoAyaka ;
using namespace std;
int T;
int main(){
	cin>>T;
	for(int q=1;q<=T;q++){
		int n,ans=0,cnt=0;
		int a[1005]={};char c[1005]={};
		cin>>n;
		for(int i=0;i<=n;i++)cin>>c[i];
		for(int i=0;i<=n;i++)a[i]=c[i]-48;//0的ASCLL码为48，字符型转为整型 
		for(int i=0;i<=n;i++){
			if(a[i]!=0){//如果这个等级没人就不需要考虑 
				if(cnt>=i)cnt+=a[i];//人够了就加起来 
				else{
					ans+=i-cnt;//i-cnt计算使当前害羞等级的人站起来需要邀请的朋友数量 
					cnt=i+a[i];//邀请以后到达害羞等级的值并加上当前害羞等级的人数 
				}
			}
		}cout<<"Case #"<<q<<": "<<ans<<endl;如题述，输出 
	}
	finner_forgeter love KamisatoAyaka//绫华··· 
}
```

---

## 作者：goIdie (赞：1)

## 思路

简单贪心。

首先明确一点，为了让站起来鼓掌的人数越多，邀请的朋友的害羞等级肯定要设为 $0$。即邀请的朋友会立即站起来鼓掌。

我们按害羞程度由低到高处理观众，维护当前站起来鼓掌的人数 $tot$。如果 $tot$ 小于当前观众的害羞程度 $i$，就邀请 $i-tot$ 个朋友，然后将 $tot$ 更新为 $i$ 并将 $tot$ 加上害羞程度为 $i$ 的观众的数量。

时间复杂度 $O(S_{max})$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,maxs,tot,ans;
string s; 
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>maxs>>s;
        tot=ans=0;
        for(int i=0;i<=maxs;i++){
            if(tot<i){
                ans+=i-tot;
                tot=i;
            }
            tot+=s[i]-'0';
        }

        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：wangmutian (赞：1)

### 题目大意
有一群观众，每个观众都有一个害羞度，即使得该观众鼓掌所需的最小鼓掌人数。题目包含 $t$ 组数据，每组数据包括一个数 $S_{max}$，代表这组数据的观众中害羞度的最大值，以及一串长度为 $S_{max} + 1$ 的字符串，第 $k$ 位数字代表害羞度为 $k - 1$ 的观众的数量。

你可以邀请任意数量的朋友来当观众并给他们分配害羞度，目标是使得所有观众都鼓掌。请求出达到目标所邀请的朋友数量的最小值。

### 题目思路
本题可以直接按照题目描述进行模拟。除此之外，可以采用贪心策略，每一步采取当前的最优方案，即在遍历害羞度为 $0 \sim S_{max}$ 观众时考虑当前总鼓掌人数是否大于当前害羞度。若不满足，则邀请好友充当观众。由于我们可以任意分配好友的害羞度，我们不妨令所有好友的害羞度为 $0$，即这些好友无论如何都会鼓掌，这样可以让当前邀请的好友最小化。

### 细节处理
由于本题的每组数据中的观众害羞度分布以字符串的形式输入，直接使用 int 类型变量存储会导致不同害羞度的观众数量被存储在了同一个变量中，因此可先定义 char 变量一位一位地输入，之后再将其转换为整型数据存入数组。

此外，本题有多组数据，每次需要重新赋值。

### 代码

```cpp
#include <iostream>
using namespace std;

int t, n, a[1010], cnt, sum; //cnt记录邀请好友数量，sum记录鼓掌人数
char op;

int main()
{
    cin >> t;
    for (int k = 1; k <= t; k++)
    {
    	cin >> n;
    	for (int i = 0; i <= n; i++)
    	{
    		cin >> op;
    		a[i] = op - '0';
    	}
    	cnt = 0;
    	sum = a[0]; //多组数据需重新赋值
    	for (int i = 1; i <= n; i++)
    	{
    		if (sum < i && a[i] > 0) //判断当前总鼓掌人数是否小于当前害羞度；若小于，则邀请好友
    		{
    			cnt += i - sum;
    			sum += i - sum;
    		}
    		sum += a[i];
    	}
    	printf("Case #%d: %d\n", k, cnt); //按照要求格式输出，可采用printf格式
    }
    return 0;
}
```

---

## 作者：llh2012 (赞：1)

### 题意
有一些观众，每个观众有一个害羞值  $S_i$，当有 $S_i$ 及以上个观众站起来鼓掌时，这个观众就会站起来。还可以喊来朋友，朋友可以作为害羞值为任意值的观众。
### 思路
按题意模拟，先让害羞值为 0 的观众站起来鼓掌，再让害羞值为 1 的观众站起来鼓掌，以此类推。当站起来鼓掌的观众数不能让害羞值更高的观众站起来鼓掌，就喊朋友来增加站起来鼓掌的观众数，让害羞值更高的观众站起来鼓掌。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,ans/*邀请朋友数*/,a[10001]/*观众害羞值*/,now/*站起来鼓掌的观众数*/;
string s;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        memset(a,0,sizeof(int));now=0;ans=0;//重置
        cin>>n>>s;
        for(int j=0;j<=n;j++)//从零开始
            a[j]=s[j]-'0';
        for(int j=0;j<=n;j++){
            if(now<j)
                ans+=j-now; 
            now+=a[j]+max(0ll,j-now);//记得加上朋友数
        }
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
  return 0;
  }
```

---

## 作者：chenyingwang (赞：1)

## 思路

贪心题，要让所有人站起来鼓掌，而只有在 $S_i$ 个人之后 $K_i$ 个人才会站起来鼓掌。要通过加入最少的朋友（在几个人之后可以自定义）让所有人鼓掌。模拟每个人站起来鼓掌的过程；如果达不到要求就增加害羞值为 $0$ 朋友，**直到**这些害羞值相同的人能鼓掌。因为害羞值是按**递增**顺序排的，如果前面的达不到要求，后面的就更不行了。而朋友的害羞值可以自由设定，就都设为 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,s,fri;
string k;
int main(){
    cin>>t;
    for(int l=1;l<=t;l++){
        // 初始化不能漏。
        s=fri=0;
        k="";
        cin>>m>>k;
        for(int i=0;i<=m;i++){ // 害羞值 max 加一个人。
            if(k[i]==0){
                continue;
            }
            else{
                while(s<i){ // 增加朋友，直到此类人可以鼓掌。
                    s++; 
                    fri++;
                }
                s+=int(k[i]-'0'); // 加到已经鼓掌的人中。
            }
        }
        cout<<"Case #"<<l<<": "<<fri<<endl;
    }
    return 0;
}
```

---

## 作者：GuoMingXuants1 (赞：0)

### 思路
这道题思路并不是很难。

由题可知，既然害羞等级为 $j$ 的观众需要前面的至少 $j$ 个观众起立鼓掌后才能鼓掌（害羞等级为 $0$ 的观众直接就起立鼓掌），那么，我们就可以从害羞等级 $0$ 的观众开始逐级向上遍历，并用一个变量 $n$ 记录目前为止害羞等级为 $j$ 的观众前面起立鼓掌的观众数量。如果 $n < j$，则这一害羞等级的观众不会起立鼓掌，那就需要邀请 $j - n$ 个朋友。用 $sum$ 记录邀请的数量，并且还要让 $n$ 加上邀请的朋友数量 $j - n$，即让 $j$ 值赋值给 $n$。再让 $n$ 加上这个害羞等级的观众的数量，用于下一层级。如果说 $ n \ge j$，说明前面观众数量管够，完全能满足当前害羞等级的观众要求，只需要加上当前害羞等级的观众数量即可。

### 代码

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int smax;
        cin>>smax;
        int n,sum;
        sum = n = 0;
        for(int j=0;j<=smax;j++)
        {
            char s[1001];
            cin>>s[j];
            if(n<j)
            {
                sum+=j - n;
                n = n + (j - n);
            }
            n += int(s[j] - 48);
        }
        cout<<"Case #"<<i<<": "<<sum<<endl;
    }
    return 0;
}
```

---

## 作者：David4119 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13211)

# 思路：
## 切入点：
因为本题的算法标签显示的是贪心，所以我们容易想到，每个朋友既然都可以随意设置“害羞等级”，那为什么不提高利用率，把他们都设置为 0 吗？这是本题的第一个关键点。

而根据题目的描述，害羞等级为 $i$ 的观众仅会在场上已经站起来 $ \ge i$ 个人时才起立，而场上站着的总人数又会加上此人数，这不就是前缀和吗？

## 算法：
首先，读入字符串并将其每个字符分离并转换成整型存入数组 $a$，再新建一个累加器 $ans=0$，用来存储朋友数量。这里可以用一种讨巧的办法，直接用格式化输入获取一位域宽的数字存进 $a$。

对于每个 $a_i$,只需先判断 $a_{i-1}$ 是否比 $i$ 小。如果答案是肯定的，则将 $ans$ 加上 $i-a_{i-1}$ 的差。注意，因为已经叫了 $i-a_{i-1}$ 个朋友，所以从  $a_1$ 到 $a_{i-1}$ 都应自增 $ans$。由于之后无需用到 $a_{i-1}$ (不含)之前的元素，所以只需将 $a_{i-1}$ 加上 $ans$，也就是 $i-a_{i-1}$,变为 $i$ 即可。最后，记得用前缀和的方式，把 $a_i$ 再加上 $a_{i-1}$。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        int s,ans=0;
        cin>>s;
        int a[s+1];
        for(int j=0;j<=s;j++){
            scanf("%1d",&a[j]);
            if(a[j-1]<j){
                ans+=j-a[j-1];
                a[j-1]=j;
            }
            a[j]+=a[j-1];
        }
        printf("Case #%d: %d\n",i,ans);
    }
    return 0;
}//本题较简单，就不做注释了
```

求过求赞

---

## 作者：SatoruXia (赞：0)

思路是逐个遍历害羞等级，检查当前场上的人数是否足以让遍历到的害羞等级的观众站起来。如果人数为 $0$ 直接跳过；否则如果可以就将站起来的总人数加上这个数值，如果不能就添加朋友的数量，（肯定能想到将朋友的害羞值全设为 $0$ 就行了）直至他们能够站起来为止。最后计算出的肯定是最优解，因为每次在场所有人均被利用。  
注意如果处理字符串时使用下标的访问方式，下标与数组一样也是从 $0$ 开始的。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        int MAXM, tot = 0, ans = 0, num; //tot表示当前站起来的人数，ans表示朋友总数
        string s;
        cin >> MAXM >> s;
        for (int k = 0; k <= MAXM; k++) { //逐个遍历
            num = s[k] - '0'; //将字符转化为数值
            if (num == 0) continue; //跳过
            if (tot < k) { //需要增加朋友的情况
                ans += k - tot; //补上
                tot = k; //更新
            }
            tot += num; //要加上新站起来的人
        }
        //输出
        cout << "Case #" << i << ": " << ans << endl;
    }
    return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
~~听说这题原时限 480 秒。~~
### 题目大意
最少加 $k$ 人，使得 $S_i \ge \sum _ {j = 0} ^ i S_j +k$。

根据这条式子，我们可以知道若 $S_0$ 为零，则至少要先加一个人，一次类推。

由于数据规模小且时限较大，直接遍历 $S$，进行模拟，比较并记录当前至少需要的人数以及已有人数。

**注意：** 因为是多组数据，变量请初始化！

## 参考代码

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int t,n,cnt,ans;
string s;
char ch;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>n;
		ans=cnt=0;//注意初始化 
		for(int i=0;i<=n;i++){
			cin>>ch;
			if(i==0&&ch=='0') cnt++,ans++;
			else if(cnt<i&&i!='0') ans+=i-cnt,cnt=i;
			cnt+=ch-'0';
		}
		cout<<"Case #"<<o<<": "<<ans<<'\n';
	}
}
/*
*/
```

---

## 作者：Hkb150429 (赞：0)

## 题意

最初，所有观众都坐着。每位观众都有一个“害羞等级”。害羞等级为 $S_i$ 的观众会等到至少有 $S_i$ 位其他观众已经站起来鼓掌后，才会立即站起来鼓掌。如果 $S_i = 0$，那么这位观众会无论如何都立刻站起来鼓掌。
请问你至少需要邀请多少位朋友，才能保证全场起立鼓掌？

## 思路

以`111000111`举例：


| $i$ | 0 | 1 | 2 | 3 | 4 | 5 |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| $ans$ |$0$|$0$| $0$ | $0$ | $2$ | $2$ |
| $now$ | $1$ | $2$ | $2$ | $2$ | $5$ | $6$ |
|字符串| $1$ | $1$ | $0$ | $0$ | $1$ | $1$ |

我们知道，如果 $now < i $，那么最优的方法就是让 $now$ 与 $i$ 的关系变成 $now = i$，$ans$ 也要增加，以此类推，我们就可以实现这段代码了。

## AC code

```
#include<bits/stdc++.h>
using namespace std;
int a[1005],sm,now=0,ans;
string s;
int main(){      
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        now=0;
        ans=0;
        cin>>sm>>s;
        for(int j=0;j<=sm;j++){
            a[j]=(s[j]-'0');
        }
        for(int j=0;j<=sm;j++){
            if(a[j]==0)continue;
            if(now>=j)now+=a[j];
            else ans+=j-now,now+=j-now+a[j];
        }
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：shiziyu111 (赞：0)

# 题目大意

有一些人，这些人分为不同的害羞等级，每个人只有在鼓掌人数 $\geq$ 自身害羞等级时，才会站起来鼓掌，请问你最少要找几个人~~当托~~一起鼓掌。

# 分析

我们只需要不断枚举害羞等级，统计鼓掌人数，在当前鼓掌人数 $<$ 害羞等级时加上朋友就行了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		int n,sum=0,friends=0;
		cin>>n;
		string s;
		cin>>s;
		sum+=s[0]-'0';
		for(int i=1;i<=s.size();i++)
		{
			if(i>sum)
			{
				friends+=i-sum;
				sum=i;
			}
			sum+=s[i]-'0';
		}
		cout<<"Case #"<<t<<": "<<friends<<"\n";
	}
	return 0;
}
```

---

