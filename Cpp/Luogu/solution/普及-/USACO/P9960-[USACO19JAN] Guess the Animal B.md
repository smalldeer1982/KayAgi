# [USACO19JAN] Guess the Animal B

## 题目描述

奶牛 Bessie 和她的朋友 Elsie 厌倦了她们的坚果壳游戏，她们想要玩另一个叫做“猜动物”的常见游戏。

游戏开始时，Bessie 会想好一种动物（大部分时候，她想的都是奶牛，这使得游戏相当无聊，但是偶尔 Bessie 也能有些新意，想一些别的）。随后 Elsie 会通过问一些问题来猜出 Bessie 选择的动物。每个问题都是询问这种动物是否具有某个特定的特征，Bessie 对于每个问题回答“是”或“不是”。例如：

Elsie：“这种动物是能飞的吗？”  
Bessie：“不是。”  
Elsie：“这种动物是吃草的吗？”  
Bessie：“是。”  
Elsie：“这种动物是能产奶的吗？”  
Bessie：“是。”  
Elsie：“这种动物是会哞哞叫的吗？”  
Bessie：“是。”  
Elsie：“这样的话我想这种动物是奶牛。”  
Bessie：“猜对了！”  

如果我们将所有具备符合 Elsie 到目前为止所提出的问题的特征的动物的集合称为“可行集”，那么 Elsie 会持续进行提问直到可行集仅包含一种动物，然后她会把这种动物作为她的答案。对于每个问题，Elsie 会选择某种动物的一个特征进行询问（即使这个特征并不能进一步帮助她缩小可行集）。她不会关于同一个特征询问两次。

给定 Bessie 和 Elsie 知道的所有动物以及它们的特征，请求出 Elsie 在猜出正确的动物之前能够得到的“是”的回答的最大数量。 

## 说明/提示

### 样例解释 1

在这个例子中，Elsie 可能在对话中获得 $3$ 个“是”的回答（题目中的例子），并且不可能进行包含超过 $3$ 个“是”的回答的对话。 

## 样例 #1

### 输入

```
4
bird 2 flies eatsworms
cow 4 eatsgrass isawesome makesmilk goesmoo
sheep 1 eatsgrass
goat 2 makesmilk eatsgrass```

### 输出

```
3```

# 题解

## 作者：Karl_Aldrich (赞：2)

## 思路
~~模拟~~
### 裸题
给出 $n$ 个集合，每个集合 $s_i$ 给出 $k$ 个元素，求出 $n$ 个集合中，最大共同交集的的大小。
### 实现思路
1.读取动物和它们的特征，将它们存储在一个数据结构中，其中动物名称映射到特征集合。

2.遍历所有动物对，比较它们的特征，找出共同的特征数量。

3.记录最大的共同特征数量，并在最后的结果上加 $1$。

4.输出结果作为 `Elsie` 能够获得的最大“是”的回答数量。 
## 代码
（详细解释在代码里）
```cpp
#include<bits/stdc++.h>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
using namespace std;
int n;
unordered_map<string,unordered_set<string>>a;//存储动物和对应的特征
int ans;
int main(){
    cin>>n;
    //输入
    for(int i=1;i<=n;++i){
        string name;
        int k;
        cin>>name>>k;
        unordered_set<string>f;
        for(int j=0;j<k;++j){
            string tmp;
            cin>>tmp;
            f.insert(tmp);//将特征记录在集合中
        }
        a[name]=f;//动物和特征集合映射存入哈希表
    }
    //遍历所有动物，对比特征
    for(auto i=a.begin();i!=a.end();++i){
        for(auto j=a.begin();j!=a.end();++j){
            if(i->first!=j->first){//确保不是同一种动物
                int cnt=0;
                //找出相同特征
                for(auto k:i->second){
                    if(j->second.count(k)>0)cnt++;
                }
                //记录最大共同特征
                ans=max(ans,cnt);
            }
        }
    }
    //输出
    cout<<ans+1<<endl;
    return 0;
}
```


---

## 作者：T_TLucas_Yin (赞：2)

获得“不是”的回答的询问对结果没有丝毫影响，不考虑。

容易想到，每一次获得“是”的回答都会让目标区间缩小。区间大小缩小到 $1$ 的时候游戏就会结束。因此，若全局最多提问 $m$ 次，则说明第 $m$ 次提问时目标区间中至少还可以有 $1$ 个动物没有被排除。第 $m$ 次提问后被排除的动物肯定是与答案的特点最接近的，否则它们就会在之前的提问中被排除。

反过来想，既然我们不知道目标动物，也就不能确定最后一个被排除的是谁。但是，我们知道所有动物的特点，因此可以找拥有最多相同特点的两个动物，让它们中的任意一个做为答案动物，另一个做为第 $m$ 次被排除的动物，这样构造就能使得提问的次数最多。

由于数据范围够小，因此只需要枚举所有动物的两两搭配，找出其中重复特点最多的一组就行了。注意答案是它们重复特点的数量 $+1$，因为在询问所有重复特点后还要再询问一次才能区分开这两个动物。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],ans;
string s[105][105],c;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c>>a[i];
        for(int j=1;j<=a[i];j++) cin>>s[i][j];
    }
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
        int cnt=0;
        map<string,bool> m;
        for(int k=1;k<=a[i];k++) m[s[i][k]]=1;//使用map来存储一个动物的特点
        for(int k=1;k<=a[j];k++) if(m[s[j][k]]) cnt++;
        ans=max(ans,cnt);
    }
    cout<<ans+1;
    return 0;
}
```

---

## 作者：Alystkia (赞：1)

### 题意：

观察样例，可以发现各各动物之间的特点有相同也有不相同的。而题目求的是最大值，所以只需要比较每两个动物之间，相同特点的数量，最后比较出最大值加一。因为答案只为一个动物，所以需要加上另一个动物没有的特点。

### 思路：
看下题，发现 $2 \leq N  \leq100$，$1 \leq K \leq 100$.

于是直接就可以联想到暴力解题。

1. 动物名称没有用处，所以只输入不用存储。但是 $k$ 和动物特点需要存储，因为后面需要进行比较。

2. 每两个动物之间进行比较，比较出某两个动物之间，特点相同数最多的值。

3. 将这个值 $+1$.

按照这个思路，只需要 $4$ 个循环就足够了，所以完全不用担心超时。

```
#include <bits/stdc++.h>
using namespace std;
string a[110][110];
int k[110];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	string s;
    	cin>>s>>k[i];
    	for(int j=1;j<=k[i];j++)
    		cin>>a[i][j];
    }
    int maxn=0;
    for(int i=1;i<=n;i++)
    {
    	for(int j=i+1;j<=n;j++)
    	{
    		int ans=0;
    		for(int z=1;z<=k[i];z++)
    			for(int l=1;l<=k[j];l++)
    				if(a[i][z]==a[j][l])
    					ans++;
    		if(maxn<=ans)
    			maxn=ans;
    	}
    }
    cout<<maxn+1<<endl;
    return 0;
}

```
建议评橙

---

## 作者：zheng_zx (赞：1)

## P9960 [USACO19JAN] Guess the Animal B

[题目传送门](https://www.luogu.com.cn/problem/P9960)

### 分析

---

这道题就是要想尽办法让 ```Elsie``` 得到的“是”的回答更多。

就是要让她问一些正确却不能判断出答案的问题。

看一下这个数据范围：

- $2 \le N \le 100$，$1 \le K \le 100$。

数据范围很小，所以直接暴力！

依次统计出每两种动物的共同的特点，答案就是共同特点最多的动物的种数 $+1$。

### Code：

---

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, ans = 0, a[105];
string b[105][105];
int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i){
    	cin >> b[i][i] >> a[i];
        for(int j = 1; j <= a[i]; ++j)
            cin >> b[i][j];
    }
    for(int i = 1; i <= n; ++i)
    	for(int j = i + 1; j <= n; ++j){
            s = 0;
            for(int k = 1; k <= a[i]; ++k) 
                for(int l = 1; l <= a[j]; ++l) 
                    if(b[i][k] == b[j][l]){
                        ++s;
                        break;
                    }
        if(s > ans) ans = s;
    }
    printf("%d", ans + 1);
    return 0;
}
```

---

## 作者：GoodLuckCat (赞：1)

先来个 [题目链接](https://www.luogu.com.cn/problem/P9960)。

~~调了好几遍才过，原因是一段代码放错位置了。~~

题目要求我们找出 Bessie 回答“是”最多的次数。

数据范围很小，所以直接暴力对比。

因为当“可行集”里只剩下一种动物的时候，Elsie 就会马上猜出这种动物是什么，所以要想得到“是”的回答最多，必须要让提问的次数最多。而且提问时要注意要先提问大部分动物都有的特征，举一个例子（其实就是题目中的例子）：

第一次提问：flies，回答：No。此时的可行集：$\text{\{cow,sheep,goat\}}$。

第二次提问：eatsgrass，回答：Yes。此时的可行集：$\text{\{cow,sheep,goat\}}$。可行集并没有缩小，相当于浪费一次提问机会，但是回答“是”的次数多了。

现在进行了 $2$ 次提问，可行集中剩下 $3$ 个元素。但是再看一下下面这种情况：

第一次提问：isawesome，回答：Yes。此时的可行集：$\text{\{cow\}}$。

现在仅进行了 $1$ 次提问，可行集中却只剩下 $1$ 个元素了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[101][101];
int b[101];
int main()
{
    int n,t=0,s=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i][i]>>b[i];
        for(int j=1;j<=b[i];j++)cin>>a[i][j];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            for(int x=1;x<=b[i];x++)
            {
                for(int y=1;y<=b[j];y++)
                {
                    if(a[i][x]==a[j][y])
                    {
                        s++;
                        break;
                    }
                }
            }
            t=max(t,s);
            s=0;
        }
    }
    cout<<t+1;
}
```

[AC 记录](https://www.luogu.com.cn/record/140178783)

---

## 作者：Quartz_Blocks (赞：0)

很简单滴……
（也是我第一个题解 QWQ ）。

其实这题就是要我们去对比每一组与其他组字符串相同数量的最大值，虽然 for 循环 $4 $ 层嵌套，但好在这题的数据小，所以能过关。

时间复杂度为  $O( n ^ 4 )$  。

提示：用 vector 方便很多(不会用的话欢迎借鉴）。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int n;
vector <string> t[100]; //使用 vector 存储每组字符串。

int count(int i, int j){ //字符串比较函数。
    int cnt = 0;
    vector<string> x = t[i], y = t[j]; //截取每一节。
    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++) //一个一个比较。
            if (x[i] == y[j]) cnt++;
    return cnt;
}

int main(){
    cin >> n;
    string s;
    for (int i = 0;i < n;i++) {
        int k;
        cin >> s >> k;
        for(int j = 0;j < k;j++) {
            cin >> s;
            t[i].push_back(s);
        }
    }
    int mx = 0;
    for (int i = 0;i < n;i++)
        for (int j = i+1;j < n;j++)
            mx = max(mx,count(i,j)); //外层比较。
    
    cout << mx+1 << endl;
    return 0;
}
```

---

## 作者：iostream69 (赞：0)

# 题面
**[题目传送门](https://www.luogu.com.cn/problem/P9960)**

# 思路
这题的思路在看到数据范围时就了然了。

$ 2\le n \le 100,1\le k\le100$

很明显是让我们打暴力。

具体的思路的就是逐个对比两种动物之间的相同点，全部遍历一遍后找出相同点最大的两只动物，再把相同点加一然后输出。

时间复杂度 $ O({n^4}) $，虽然高但是能过。
### 要注意的点
1. 注意不要比较相同的两种动物的相同点。
2. 一定要把相同点加一再输出。
# 代码
```cpp
#include<bits/stdc++.h>
#define fzjakioi return 
using namespace std;
int n,maxn=-1;
string name[101][101];
int sum[101],sjh[101][101];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>name[i][0]>>sum[i];
		for(int j=1;j<=sum[i];j++){
				cin>>name[i][j];			
		}
    }
	for(int i=0;i<n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=0;k<=sum[i];k++){
				for(int p=0;p<=sum[j];p++){
			            if(name[i][k]==name[j][p]){
					    sjh[i][j]++;
						break;	
				    }
			    }
		    }
	    }
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(sjh[i][j]>maxn){
				maxn=sjh[i][j];
			}
		}
	}
	cout<<maxn+1<<endl;
	fzjakioi 0;
}
```

---

## 作者：carbon_monoxide (赞：0)

看到那么小的数据范围，当然直接爆搜啦！

要想让 `Bessie` 回答的“是”更多，`Elsie` 问的问题就得是正确但仍不能判断出答案的问题，问的特征就必须是很多动物共同拥有的。

所以我们可以一一枚举具有相同特点的动物，共同点最多的动物的种数加一便是答案。

为什么要加一？因为 `Elsie` 还需要多问一次以区分两种动物，才能得到答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],ans;
string s[110][110];//用map也行，但我懒
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>s[i][i]>>a[i];
        for(int j=1;j<=a[i];j++) cin>>s[i][j];
    }
    for(int i=1;i<=n;i++){
    	for(int j=i+1;j<=n;j++){
            int cnt=0;
            for(int k=1;k<=a[i];k++){
                for(int l=1;l<=a[j];l++){
                    if(s[i][k]==s[j][l]){
                        cnt++;
                        break;
                    }
                }
            }
            ans=max(ans,cnt);
    	}
    }
    cout<<ans+1;//不要忘记+1
    return 0;
}
```

---

## 作者：FlyPancake (赞：0)

# [P9960 [USACO19JAN] Guess the Animal B](https://www.luogu.com.cn/problem/P9960) 题解

结论题。

## Ideas

要想让回答“是”的次数最大，就要让 Elsie 问有共同特征的问题使之无法分辨。所以只要找每两种动物之间的共同特征条数的最大值，最后再加上 $1$ 次提问次数即可。

因为 $2 \le N \le 100$，并且 $1 \le K \le 100$，所以直接暴力枚举即可。

## Code

```
#include <bits/stdc++.h>
using namespace std;

string ani[105][105];
int cnt[105];

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin>>n;
    for(int i=1; i<=n; i++){
        cin>>ani[i][0]>>cnt[i];
        for(int j=1; j<=cnt[i]; j++){
            cin>>ani[i][j];
        }
    }
    int ans = 0;
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            int ret = 0;
            for(int x=1; x<=cnt[i]; x++){
                for(int y=1; y<=cnt[j]; y++){
                    if(ani[i][x] == ani[j][y]){
                        ret++;
                        break;
                    }
                }
            }
            ans = max(ans, ret);
        }
    }
    cout<<ans+1;
    return 0;
}
```


---

## 作者：volatile (赞：0)

# 思路

只要回答是“是”，那么就会排除掉没有这个特征的动物，那么可行集就变少了，要想“是”的回答数量最多，则提问的次数就得越多，我们提问大部分动物有的特征，“不是”的可能会比较小，且可以刷“是”的次数。注意得到的结果要加 $1$，因为最后不会只剩下一种动物，要再问一遍它们不同的特征才能得到答案。

# 代码

```cpp
#include<iostream>
#include<string>
using namespace std;
struct animals{
    string name,tz[114];
    int k;
}a[114];
int main()
{
    int n,maxn=-114514;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].name>>a[i].k;
        for(int j=1;j<=a[i].k;j++) cin>>a[i].tz[j];
    }
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            int t=0;
            for(int k=1;k<=a[i].k;k++){
                for(int l=1;l<=a[j].k;l++){
                    if(a[i].tz[k]==a[j].tz[l]){
                        t++;
                        break;
                    }
                }
            }
            maxn=t>maxn?t:maxn;
        }
    }
    cout<<maxn+1;
    cout<<endl;
    system("pause");
    return 0;
}
```


---

