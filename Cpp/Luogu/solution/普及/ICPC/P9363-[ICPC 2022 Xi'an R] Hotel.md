# [ICPC 2022 Xi'an R] Hotel

## 题目描述

你正在一个古代的酒店里为一场编程竞赛做志愿工作。酒店的历史可以追溯到秦朝，所以酒店不提供手机信号和自来水。你无法使用网络软件，不得不手动为参赛者分配房间。幸运的是，酒店拥有充足的房间，并且你有一台电脑帮你做一些计算。

共有 $n$ 个队伍，每个队伍恰有 $3$ 名选手。酒店有两种房间，单人间和双人间，分别可以容纳 $1$ 和 $2$ 名选手。为了避免使选手尴尬，如果两名选手分配到了同一个双人间，他们必须来自同一个队伍，并拥有相同的性别。

相同种类的房间的花费相同，但不同种类的房间花费可能不同。你需要计算主办方最少需要花多少钱。选手们已经在登记厅等候多时，而竞赛财务经理依靠你来节省开支，私吞剩下来的钱发大财。你需要尽快完成任务，否则财务经理将起诉你侵犯了他的名誉权！

$1\leq n, c_1, c_2\leq 1000$。

## 样例 #1

### 输入

```
3 1 3
MMM
MMM
FFF
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 3 1
ABC
DEF
GHI
```

### 输出

```
9
```

## 样例 #3

### 输入

```
10 438 438
WWW
SOU
PUN
ETC
OME
CFI
NAL
GOO
DHO
TEL
```

### 输出

```
12264
```

# 题解

## 作者：ivyjiao (赞：2)

题意：

有 $n$ 个队，每队有 $3$ 位选手，每位选手都有一个从 $\texttt{A}\sim \texttt{Z}$ 之间的编号，现在要将这 $n$ 队选手分配住宿，规则如下：

- 单人房：顾名思义。
- 双人房：住进去的两个人必须是同队同编号。

思路：

显然每个队是可以割裂开来算的。

然后直接模拟分配即可。

注意：**两个单人房可能比一个双人房划算（全单情况），一个双人房也可能比一个单人房划算（全双情况），双人房可以不住满（配合全双情况），~~不开……额不会见祖宗啊，那没事了~~**。

```cpp
#include<iostream>
using namespace std;
int n,c1,c2,ans;
char a,b,c;
int main(){
    cin>>n>>c1>>c2;
    while(n--){
        cin>>a>>b>>c;
        if(a==b){
            if(c2<=2*c1) ans+=c2;
            else ans+=2*c1;
            if(c2<c1) ans+=c2;
            else ans+=c1;
        }
        else if(a==c){
            if(c2<=2*c1) ans+=c2;
            else ans+=2*c1;
            if(c2<c1) ans+=c2;
            else ans+=c1;
        }
        else if(b==c){
            if(c2<=2*c1) ans+=c2;
            else ans+=2*c1;
            if(c2<c1) ans+=c2;
            else ans+=c1;
        }
        else{
            if(3*c2<3*c1) ans+=3*c2;
            else ans+=3*c1;
        }
    }
    cout<<ans;
}
```

---

## 作者：yinzifan (赞：1)

# [题面](https://www.luogu.com.cn/problem/P9363)

大意：给定 $n$ 个队伍的队员性别，让你求最小的花费(~~什么性别 26 个啊~~)。

# 前置知识
字符串，一定数学能力。

# 算法分析
只能同队住房，那就对每个输入进行处理。

首先很容易就能发现有两个显而易见的方案：

- 全买单间。
- 全买双人间。

取最小值即可。

### 还有没有其他方案呢？
当然，只要有两人性别相同，我们就可以让他们住进双人间，也就是一单一双的方案。

#### 有人就问了：没有两单一双的方案吗？
双人间只住一人，那么如果双人便宜，我们就该全买单人（方案一）；否则就全买双人（方案二）。所以我们已经处理过了这种情况。

# AC code

```
#include<bits/stdc++.h>
using namespace std;
int n,ans=0,c1,c2;
int main(){
	cin>>n>>c1>>c2;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		int a1=min(c1,c2)*3,a2=0,a3=0;
		if(s[0]==s[1]||s[0]==s[2]||s[1]==s[2]){
			a2=c2+c1;
			a3=c2*2;
			ans+=min(a1,min(a2,a3));
		} 
		else{
			ans+=a1;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Accepted666666 (赞：1)

# 模拟加判断

[题目传送门](https://www.luogu.com.cn/problem/P9363)
# 思路

本题可以分情况讨论：

先定义一个二维数组

```cpp
char a[1002][3];    
```

- 若单人间的一个人住比双人间的一个人住要便宜，直接全买单人间。

- 若双人间一间比单人间一间便宜，直接全买双人间。

就是这样

```cpp
if(c2/2.0>=c1){    
    printf("%d",n*3*c1); 
}
else if(c2/2.0<c1){  
    for(int i=0;i<n;i++){  
        if(a[i][0]==a[i][1]||a[i][0]==a[i][2]||a[i][1]==a[i][2]){ 
            ans+=c2+min(c1,c2); 
        }
        else ans+=min(c1,c2)*3;  
    }
    printf("%d",ans);    
}
```

然后循环依次加每一组，最后输出。
***

# 代码如下：

```cpp
#include<bits/stdc++.h>    // 超级万能头     
using namespace std;
int n,c1,c2,ans;
char a[1002][3];           //定义一个二维数组存性别(好像麻烦了)
int main(){
    scanf("%d %d %d",&n,&c1,&c2); //读入
    for(int i=0;i<n;i++) cin>>a[i][0]>>a[i][1]>>a[i][2];
    
    if(c2/2.0>=c1){        //若单人间一人比双人间一人便宜
        printf("%d",n*3*c1); 
    }
    else if(c2/2.0<c1){    //第二种情况判断
        for(int i=0;i<n;i++){  
            if(a[i][0]==a[i][1]||a[i][0]==a[i][2]||a[i][1]==a[i][2]){ //判断
                ans+=c2+min(c1,c2);   //双人加min(c1,c2);
            }
            else ans+=min(c1,c2)*3;  
        }
        printf("%d",ans);       //输出
    }
    return 0;             //完结撒花！
}
```

---

## 作者：XsIeEiKcEk (赞：1)

### 解法

有两种情况：

- $2\times c_1\le c_2$。

- 不满足前者。

第一种情况说明双人间并不比单人间便宜，即所有人住单人间更便宜，答案为 $3\times n\times c_1$。

否则，因为只有同一组的人才能住双人间，就一组一组的遍历。

- 若一组内有两人性别相同，就用双人间，另一人用双人间和单人间中价格较小者，因为单人可住双人间，答案为 $c_2+\min(c_1,c_2)$。

-  否则，都住双人间和单人间中价格较小者。答案为 $3\times\min(c_1,c_2)$。

### CODE：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,c1,c2;
    cin>>n>>c1>>c2;
    if(2*c1<=c2)cout<<3*n*c1;//情况一
    else{
        int ans=0;
        while(n--){
            string s;
            cin>>s;
            if(s[0]==s[1]||s[1]==s[2]||s[0]==s[2])ans+=c2+min(c2,c1);//若有性别相同者
            else ans+=3*min(c2,c1);
        }
        cout<<ans;
    }
    return 0;
}
```

---

## 作者：xiaoming007 (赞：1)

## 思路

本题求的是一共的最少花费，那么一个团 $3$ 个人，我们只需对于每个团的人进行一个求最小花费的操作即可。

本题考察的还是细心方面吧：

首先肯定存在这样的方案：

- 全买单人间。

- 全买双人间。

当至少 $2$ 个人同性别时，还多出一种方案：

- 一个单间，一个双间。

对于每个团队所可能的花费情况进行取最小值，最后得到答案相加即可。

## 代码

```cpp
#include <iostream>
using namespace std;
int main(){
    int n, c1, c2;
    cin >> n >> c1 >> c2;
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        string s;
        cin >> s;
        if(s[0] == s[1] || s[0] == s[2] || s[1] == s[2]) ans += min({c1*3, c2 + c1,c2 * 2});
        else ans += min(c1, c2) * 3;
    }
    cout << ans << '\n';
    return 0;
}
```

---

