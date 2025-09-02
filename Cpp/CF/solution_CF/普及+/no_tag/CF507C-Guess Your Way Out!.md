# Guess Your Way Out!

## 题目描述

Amr bought a new video game "Guess Your Way Out!". The goal of the game is to find an exit from the maze that looks like a perfect binary tree of height $ h $ . The player is initially standing at the root of the tree and the exit from the tree is located at some leaf node.

Let's index all the leaf nodes from the left to the right from 1 to $ 2^{h} $ . The exit is located at some node $ n $ where $ 1<=n<=2^{h} $ , the player doesn't know where the exit is so he has to guess his way out!

Amr follows simple algorithm to choose the path. Let's consider infinite command string "LRLRLRLRL..." (consisting of alternating characters 'L' and 'R'). Amr sequentially executes the characters of the string using following rules:

- Character 'L' means "go to the left child of the current node";
- Character 'R' means "go to the right child of the current node";
- If the destination node is already visited, Amr skips current command, otherwise he moves to the destination node;
- If Amr skipped two consecutive commands, he goes back to the parent of the current node before executing next command;
- If he reached a leaf node that is not the exit, he returns to the parent of the current node;
- If he reaches an exit, the game is finished.

Now Amr wonders, if he follows this algorithm, how many nodes he is going to visit before reaching the exit?

## 说明/提示

A perfect binary tree of height $ h $ is a binary tree consisting of $ h+1 $ levels. Level $ 0 $ consists of a single node called root, level $ h $ consists of $ 2^{h} $ nodes called leaves. Each node that is not a leaf has exactly two children, left and right one.

Following picture illustrates the sample test number $ 3 $ . Nodes are labeled according to the order of visit.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507C/1071268d93324fbfe90557eb5569861c59d6d7a2.png)

## 样例 #1

### 输入

```
1 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
5```

## 样例 #3

### 输入

```
3 6
```

### 输出

```
10```

## 样例 #4

### 输入

```
10 1024
```

### 输出

```
2046```

# 题解

## 作者：Ayano_Kimishima (赞：10)

思路如同楼顶 dalao，每次访问子树，若子树不包含目标，则直接加上这棵子树的所有节点，最后加上来时路径即深度即可。来时路径即目标点到根节点的路径，见代码部分：
```
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
#define int long long//记得开long long
int ans,h,n,Flag=0;
void dfs(int deep,int l,int r,int flag)//flag记录左右，1为向左，0为向右
{
	if(Flag)//已找到目标点，直接返回
		return;
	if(deep==1)//来到叶子节点 
	{
		if(l==n&&r==n)//找到目标节点 
		{
			Flag=1;
			return;
		}
		ans++;
		return;
	}
	if(n<l||n>r)//子树不包含目标节点 
	{
		ans+=(r-l+1)*2-1;//直接加上该子树节点数量 
		return;
	}
	int mid=l+r-1>>1;
	if(flag==1)
		dfs(deep-1,l,mid,0),dfs(deep-1,mid+1,r,1);
	else
		dfs(deep-1,mid+1,r,1),dfs(deep-1,l,mid,0);//注意访问顺序，先右再左
}
signed main()
{
	cin>>h>>n;
	int son=pow(2,h);//叶子节点数量
	dfs(h+1,1,son,1);
	cout<<ans+h;//加上来时深度
	return 0;
}
```

---

## 作者：trsins (赞：4)

模拟题意，几乎没有任何算法。

记录当前所处位置以及下一步往左还是往右。

每次判断目标在哪一棵子树内。

- 如果在目标的子树里面，那就继续走。

- 如果不在，就说明要把当前去的子树整棵走一遍，那么把答案加上那棵子树的大小，并直接跳过，然后走到下一棵子树的根节点去，注意**方向不变**。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507C/1071268d93324fbfe90557eb5569861c59d6d7a2.png)

解释一下。

如图，好比说走完了 $2$ 号后直接跳过子树，跳到 $9$ 号。由于原本的 $2$ 是向左跳到 $3$ 的，然后到 $8$ 回溯时，因为二叉树子树节点为偶数个这一性质，所以 $8$ 会回溯至 $1$ 然后到 $9$ ，此时 $1$ 到 $9$ 的方向也和一开始的 $2$ 到 $3$ 一样是向右。

最优解祭。

---

## 作者：三点水一个各 (赞：4)

### 思路

拿h=3，n=6时做，如图:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507C/1071268d93324fbfe90557eb5569861c59d6d7a2.png)

从目标结点开始，如果它可以按照规则到达它的父结点，那么它的父结点的另一部分的子树可以有生之年都不会经过了（如图，E左边的结点不会经过）

再依次判断它的父结点，直到根节点为止。

### 实现

记录下当前结点的来时的方向（初始为1），
如果它上次的方向与这次不同，那么就删掉另一部分的结点。


```
#include<cstdio>
#include<cstring>
#include<math.h>
using namespace std;
long long h,n,pre,pre2,ans;
int main()
{
    scanf("%lld%lld",&h,&n);
    ans=pow(2,h+1)-1; pre=1;  //ans用于减去不需要的结点，pre记录上次来时的方向
    while(h--)
    {
        if(pow(2,h)>=n) pre2=-1;  //if判断这次来时的方向
        else n-=pow(2,h),pre2=1;
        if(pre*pre2==-1) ans-=pow(2,h+1)-1;  //删除有生之年不会经过的结点
        pre=pre2;
    }
    printf("%lld\n",ans-1);  //别忘了-1
    return 0;
}

```

---

## 作者：Rt__ (赞：1)

[ CF507C Guess Your Way Out!](https://www.luogu.com.cn/problem/CF507C)

dfs 好题
## 题意简述
给一棵深度为 $h+1$ （我习惯深度算上根节点）的满二叉树，最后一层的叶子节点从左往右依次标号为 $1,2,3... 2^{h}$ ，按左儿子，右儿子，左儿子，右儿子 … 的顺序遍历，求出遍历到第 $n$ 个叶子节点时，搜过了多少个节点。
## 思路
根据满二叉树的性质，我们可以求出以任意深度的节点为根节点的子树中有**多少个叶子节点**，以及**多少个节点**。由于左右子树完全相同，他们的大小和包含的叶子节点个数就可以用预处理的根节点深度对应求出。

我们先以优先搜左子树为策略搜一遍，如果左子树的叶子节点个数小于当前的 $n$ ，就先搜左子树（用预处理的信息 $O(1)$ 求出）再搜右子树；同理，如果大于，就只搜左子树；等于的话就直接结束。这样我们可以得出一个答案。

然后我们发现，对于某一深度，题中策略和我们的策略的关系可能有以下四种情况

1.  题中先搜左节点后搜右节点，我们先搜左节点后搜右节点
2.  题中只搜右节点，我们先搜左节点后搜右节点
3.  题中只搜左节点，我们只搜左节点
4.  题中先搜右节点后搜左节点，我们只搜左节点

容易看出，我们的策略错误的只有第二种和第四种。所以我们可以考虑后面对错误的策略进行纠正。先在上面的搜索中保存每一个深度最后搜了左还是右节点，然后再看题中对应深度的策略是什么。对于第二种，就减去一个左子树的大小；对于第四种，就加上一个右子树大小。而如果当前是在左子树的根节点，下一个正确策略应该是右节点；如果当前节点是右子树的根节点，下一个正确策略就是左节点。直接加减即可。时间复杂度 $O(2h)$。
## 代码（马蜂良好）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 110;

int sizee[N], num[N], n, h, ans;
bool r[N];
void dfs(int deep){
	//cout << deep << ' ' << num[deep] << ' ' << sizee[deep] << endl;
	if(num[deep] < n){
		n -= num[deep];
		ans += sizee[deep];
		r[deep] = 1;
	}
	if(num[deep] == n){
		n -= num[deep];
		ans += sizee[deep] - 1;
		for(int i = deep + 1; i <= h; i++){
			r[i] = 1;
		}
		return;
	}
	ans++;
	dfs(deep + 1);
}
signed main(){
	cin >> h >> n;
	h ++;
	for(int i = 1; i <= h; i++){
		sizee[i] = (1ll << (h - i + 1)) -1;
		num[i] = 1ll << (h - i);
	}
//预处理

	dfs(1);
//先左后右搜一遍

	bool lr = 0;//当前正确策略是什么（0左1右）
	for(int i = 2; i <= h; i++){
		if(r[i] == 1 && lr == 1){
			ans -= sizee[i];
		}//情况 2
		if(r[i] == 0 && lr == 1){
			ans += sizee[i];
		}//情况 4
		lr = !r[i];
	}
//纠正策略

	cout << ans;
	return 0;
}
```

---

## 作者：TachibanaKanade (赞：1)

考虑从目标结点走回根节点而非从根结点出发。

从目标结点开始不断往父结点回溯，如果它可以按照题意所定的一左一右的方向走的话，那么另一部分子树就不会被走到。换而言之，如果每一次走的方向与前一次走的方向相反，就说明在正向走的情况下是不会走到另一部分子树的。

而如果某一次走的方向与前一次相同的话，则会走到另一半的子树，此时必然会走完该子树的所有结点后才会返回。所以直接加上那一部分子树的全部结点数即可。

对于实现而言，可以先加上所有结点，再从下往上把不会走到的子树的结点全部减掉即可。

记得开 `long long`。且最后要把目标结点本身减去。

---

## 作者：ZLCT (赞：0)

# CF507C Guess Your Way Out!
## 题意
有一棵高度为 $h$ 的满二叉树，叶子结点从左向右编号分别为 $1,2,3…2^h-1,2^h$。现在从根节点按照 LRLR 的顺序遍历二叉树，若走到叶子结点则回溯，如果下一个结点被遍历，则跳过此操作，如果连续两个操作被跳过，则回溯到父结点。求走到编号为 $n$ 的叶子结点前一共走了多少点。
### 模拟样例
按照样例所给的图进行模拟，可以发现如果走到一个不包含 $n$ 号叶子结点的子树，则会将子树全部走完。\
具体证明需要仔细阅读题干，会发现只有两次操作都跳过才会会到父亲结点，而连续的两次操作一定是不同的，所以两次操作跳过等价于子结点都被遍历。\
因此我们就可以模拟题目走的过程，如果下一个走的子树不包含目标叶子，则答案加上该子树的大小。
### 复杂度分析
因为每次都会向下跳一层，于是最多跳树的高度次，复杂度就是 $O(h)$。
### code（注意位运算 $1$ 后的 ll）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,n,ans;
void dfs(int id,int high,int lst,char nxt){
    if(high==0){
        cout<<ans<<'\n';
        exit(0);
    }
    if(nxt=='L'){
        if((1ll<<(high-1))<lst){
            ans+=(1ll<<high);
            dfs(id+(1ll<<high),high-1,lst-(1ll<<(high-1)),'L');
        }else{
            ans++;
            dfs(id+1,high-1,lst,'R');
        }
    }else{
        if((1ll<<(high-1))>=lst){
            ans+=(1ll<<high);
            dfs(id+1,high-1,lst,'R');
        }else{
            ans++;
            dfs(id+(1ll<<high),high-1,lst-(1ll<<(high-1)),'L');
        }
    }
}
signed main(){
    cin>>h>>n;
    dfs(1,h,n,'L');
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## CF507C Guess Your Way Out! 题解
### 算法
模拟
### 思路
按照左右左右的方式先往下找，每次找到一个子节点时就看此节点为根的子树是否包含目标节点，如果包含就继续往下走，不包含说明目标叶子节点在另一边的子树上，那么肯定是先需要把这边的子树遍历完才能换到另一边，所以答案直接加上这个子树的大小。

代码中 $cz$ 代表操作是左还是右，通过亦或实现取反的操作。注意要开 `long long`。本题主要需要掌握二叉树的各种性质，基本不需要算法。
### 示例代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace Ryan
{
    int h, n;
    signed work()
    {
        cin >> h >> n;
        int cz = 0;
        int end = pow(2, h - 1);
        int ans = 0;
        for (int i = h - 1; i >= 0; i--)
        {
            ans++;
            if (!cz)
            {
                if (n > end)
                {
                    ans += (pow(2, i + 1) - 1);
                    if (i)
                        end += pow(2, i - 1);
                    cz ^= 1;
                }
                else if (i)
                    end -= pow(2, i - 1);
            }
            else
            {
                if (n <= end)
                {
                    ans += (pow(2, i + 1) - 1);
                    if (i)
                        end -= pow(2, i - 1);
                    cz ^= 1;
                }
                else if (i)
                    end += pow(2, i - 1);
            }
            cz ^= 1;
        }
        cout << ans << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Ryan::work();
}
```

---

## 作者：Gmt丶FFF (赞：0)

一个节点如果在这个树的右半边，那一定会先走完左边再走到这个点。

如果一个节点在这个树的左半边，且在左半边的左半边，那一定会先走完右半边才会走到这个点。

那么我们每次只需要判断一个节点的祖先节点会先往哪个方向走即可。

可以用分治简化这个过程。

如果一个节点在树的右边，答案加上左子树结点个数。

如果一个节点在树的左边，答案不累加，将树进行水平翻转。

最后将累计的答案加上从根走到叶子节点的节点数量，即树的高度即可。

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,h;
signed main()
{
	scanf("%lld%lld",&h,&n);
	int ans=h;
	for(int i=1ll<<(h-1ll);i>0;i>>=1ll)
	{
		if(n>i)ans+=(i<<1ll)-1ll,n-=i;
		else n=i-n+1ll;
	}
	printf("%lld",ans);
	return 0;
}
```


---

