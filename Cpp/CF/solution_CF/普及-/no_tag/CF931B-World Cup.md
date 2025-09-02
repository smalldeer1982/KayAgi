# World Cup

## 题目描述

世界杯足球赛的最后一个阶段是使用决赛系统进行的。

这个阶段还有n个团队，从1到n枚举。举行了几轮比赛，每轮比赛中，剩下的队伍按照ID的顺序进行排序，然后按此顺序的第一个队与第二个队比赛，第三个队与第四个队比赛，第五个队与第六个队比赛，依此类推。保证每轮比赛都有偶数支球队。每场比赛的胜利者晋级下一轮，失败者被淘汰出局，没有平局。在最后一轮比赛中，只有剩下的两支球队参加：这轮比赛称为决赛，获胜者称为冠军，比赛结束。

Arkady想让他最喜欢的两支球队参加决赛。不幸的是，团队ID已经确定了，而且可能会发生这样的情况：如果团队足够强大的话，他们就不可能在决赛中相遇，因为他们将在更早的阶段相遇。确定ID A和B的团队可以在哪一轮会面。

## 说明/提示

在第一个例子中，1队和2队在第一轮比赛中相遇。

在第二个例子中，2队和6队只能在第三轮比赛中相遇，这是决赛，前提是他们在前几轮中赢得了所有的对手。

在第三个例子中，如果在第一轮中赢得对手，IDS7和55的球队可以在第二轮中相遇。

## 样例 #1

### 输入

```
4 1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 2 6
```

### 输出

```
Final!
```

## 样例 #3

### 输入

```
8 7 5
```

### 输出

```
2
```

# 题解

## 作者：LRL65 (赞：1)

打完代码后才发现和上面这楼大佬有点撞了，不过恳求管理能通过这篇题解。

首先，看了眼题目，感觉很简单，再一看，不就是一个模拟吗。

那接下来要知道的有几点：

- 每一局a和b只要分别:**a=a/2+a%2**(拿a举例)(如果不理解这个，可以自己推一下)
- 然后每一局n都要除以2
- 每一局计数，最后看下n是否等于1，是说明最后只有a和b，否说明除了a和b还有其他队

知道这些后就很简单了，代码：
```cpp
#include<Bits/stdc++.h>
using namespace std;
int n,a,b,s=0;
int main() {
	cin>>n>>a>>b;//输入
	while(a!=b) {//a和b不等时循环
		a=a/2+a%2;
		b=b/2+b%2;
		s++;//累加
		n/=2;
	}
	if(n!=1)cout<<s<<endl;//输出
	else cout<<"Final!"<<endl;
}
```


---

## 作者：LuffyLuo (赞：0)

这道题很简单。

我的思路和下面的大佬不一样，纯模拟，我跟大家说一下，我就以题目给出的输入二为例吧：

```cpp
输入：
8 2 6
我为大家手动模拟一下：
第一轮：1 VS 2  3 VS 4  5 VS 6  7 VS 8
第二轮：2 VS 3  6 VS 7
第三轮：2 VS 6
so Final!
```
大家不难看出题目赋予 $a$ 队与 $b$ 队超神的运气，所以他们肯定能够打败其他人，但其他的不可以，所以可以随便谁打赢。

看完这个之后大家肯定就会想到，用数组模拟上述情况就是我的思路，我只想说没错，所以我直接上代码：
```cpp
#include<bits/stdc++.h>
const int MAX=110000;
using namespace std;
int s[MAX];//就是储存每次比赛结束的结果
int main(){
	int n,i,j,a,b,ans=0,k;//ans用来保存比赛的次数
	scanf("%d %d %d",&n,&a,&b);
	for(i=1;i<=n;i++)
		s[i]=i;
	while(1){
		ans++;
		k=0;//编号，每一次比赛的编号。
		for(i=1;i<=n;i+=2){
			if(s[i]==a&&s[i+1]==b||s[i]==b&&s[i+1]==a){
				if(n!=2){
					printf("%d",ans);
					return 0;
				}
				else{//如果进入决赛
					printf("Final!");
					return 0;
				}
			}
			else if(s[i]==a||s[i+1]==a){
				k++;
				s[k]=a;
			}
			else if(s[i]==b||s[i+1]==b){
				k++;
				s[k]=b;
			}
			else{
				k++;
				s[k]=s[i+1];
			}
		}
		n/=2;//n为接下来的人数
	}
	return 0;
}
```
//不用说谢谢，不因客套，只因能见您的笑容，以及您电脑上的AC，您已经回报。

//祝大家信息学越来越棒哦！

---

## 作者：sakuyu (赞：0)

简单思考一下，可以将此题类比为二叉树

自低向上推一下下标，就会是这样子（不会搞图有点丑）：

  .........0

....1......... 2

.1....2....3....4..

1 2 3 4 5 6 7 8

如果我们定义俩队一队为A队，一队为B队

那么是不是很容易发现AB相遇的场数就是他们最近的父节点
那就可以写代码了QAQ
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define ull unsigned long long
const int INF = 0x3f3f3f3f;
const ll LINF = 1ll<<60;
const int mod=1e9+7;

int main() {
    int n,l,r;
    cin>>n>>l>>r;
    int cnt=0,tem=0;
    while(1){//找二叉树的层数;
        n/=2;
        tem++;
        if(n==1) break;
    }
    while(1){//找最近的公共父节点
        l=(l+1)/2;//向上取整
        r=(r+1)/2;//同上
        cnt++;
        if(l==r) break;//若l==r,则找到父节点，且最近
    }
    if(cnt==tem) cout<<"Final!"<<endl;
    else cout<<cnt<<endl;
    return 0;
}

```



---

## 作者：αnonymous (赞：0)

极为简单的一道水题，**暴力模拟**即可食用，思路如下：如果奇数球队赢球，则位置变成第n/2+1；如果偶数球队赢球，则位置变成n/2（简单推理，自己想想）。接下来，上代码：
```cpp
#include <iostream>
using namespace std;
int n,a,b,total;	
int main(){
	cin>>n>>a>>b;
	while(a!=b){//不冲突则两只球队不在同一组
		if(a%2==1)
			a=a/2+1;
		else
			a=a/2;
		if(b%2==1)
			b=b/2+1;
		else
			b=b/2;
		total++;//计数
		n/=2;//每次球队减少一半
	}
	if(n!=1)//如果剩下来不止一只球队，则a和b没有都进入决赛
		cout<<total;
	else
		cout<<"Final!";
	return 0;
}
```


---

