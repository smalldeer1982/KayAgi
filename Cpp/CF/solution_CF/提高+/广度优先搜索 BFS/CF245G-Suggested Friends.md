# Suggested Friends

## 题目描述

Polycarpus works as a programmer in a start-up social network. His boss gave his a task to develop a mechanism for determining suggested friends. Polycarpus thought much about the task and came to the folowing conclusion.

Let's say that all friendship relationships in a social network are given as $ m $ username pairs $ a_{i},b_{i} $ $ (a_{i}≠b_{i}) $ . Each pair $ a_{i},b_{i} $ means that users $ a_{i} $ and $ b_{i} $ are friends. Friendship is symmetric, that is, if $ a_{i} $ is friends with $ b_{i} $ , then $ b_{i} $ is also friends with $ a_{i} $ . User $ y $ is a suggested friend for user $ x $ , if the following conditions are met:

1. $ x≠y $ ;
2. $ x $ and $ y $ aren't friends;
3. among all network users who meet the first two conditions, user $ y $ has most of all common friends with user $ x $ . User $ z $ is a common friend of user $ x $ and user $ y $ $ (z≠x,z≠y) $ , if $ x $ and $ z $ are friends, and $ y $ and $ z $ are also friends.

Your task is to help Polycarpus to implement a mechanism for determining suggested friends.

## 说明/提示

In the first test case consider user David. Users Mike and Tank have one common friend (Gerald) with David. User Kate has no common friends with David. That's why David's suggested friends are users Mike and Tank.

## 样例 #1

### 输入

```
5
Mike Gerald
Kate Mike
Kate Tank
Gerald Tank
Gerald David
```

### 输出

```
5
Mike 1
Gerald 1
Kate 1
Tank 1
David 2
```

## 样例 #2

### 输入

```
4
valera vanya
valera edik
pasha valera
igor valera
```

### 输出

```
5
valera 0
vanya 3
edik 3
pasha 3
igor 3
```

# 题解

## 作者：insolublehco3 (赞：1)

# CF245G Suggested Friends

这是蒟蒻的第一篇题解 QwQ，如果有讲得不好的地方敬请谅解，并欢迎大佬在下方评论区提出宝贵的意见。

首先呢，

我们来看看这道题的题意。

这道题要输入用户的名字对，并统计用户的个数。仔细想想，我们会发现如果用朴素做法，会变得很麻烦，所以我们搬出了 stl。去重我们一般使用 map，因为操作图的时候，我们要使用一个序号与名字对应，所以我们在 map 里定义两个类型，string 和 int，其中，又因为我们要进行搜索，所以 string 放在前面用作 key。

```cpp
map<string,int> name;
map<string,int>::iterator iter; // 操作容器

int ix,it,tot;// tot 是唯一用户的数量，ix，iy 为当前用户唯一 id
for(int i=1;i<=m;++i){  
    cin>>x>>y;// 输入用户名字
    iter=name.find(x);// 查找是否已存在
    if(iter!=name.end())  ix=iter->second; // 操作容器的值不为map的尾巴，说明存在
    else name.insert(pair<string,int>(x,ix=++tot)); //不存在，插入并顺手将当前 id 设为用户数量自增后的结果
    iter=name.find(y);
    if(iter!=name.end())  iy=iter->second;
    else name.insert(pair<string,int>(y,iy=++tot));
}
```

接下来，我们就要进行图论部分的操作了。
老规矩，因为这道题考查的是图中单点对单点的关系，所以我们就不使用结构体了，转而使用 stl 中的 vector。

先定义一个 vector：`vector<int> ship[MAXN<<1];`。

注意，由于图是无向的，所以要添加两次，故定义时 `MAXN` 要乘 2（二进制写法为 `<<1`）。

然后在上面输入中，加入：

```cpp
for(int i=1;i<=m;++i){ 
    // 此处省略上方代码
    ship[ix].push_back(iy);
    ship[iy].push_back(ix);
}
```

图输入后之后，就可以进行操作了，使用循环来对每个用户进行分析。

根据题意，推荐好友双方必须互不为好友，故我们先要标记一下当前循环到的用户 $i$ 与其他用户 $j$ 是否为好友（别忘了先 `memset` 下喔）。

```cpp
for(int i=1;i<=tot;++i){
    memset(flag,0,sizeof flag);
    for(int j=0;j<ship[i].size();++j) flag[ship[i][j]]=1;
}
```

接着，我们来判断用户 $i$ 的推荐好友，如果循环两方 $i$ 和 $j$ 相同或是好友，就跳过。

如果上方条件都不满足，那么就继续判断。

再用一个子循环来判断 $j$ 的好友是不是 $i$ 的好友，如果是，就把 $i$ 和 $j$ 的共同好友数量加 1
找完之后，我们再看看 $i$ 和 $j$ 共同好友的数量是不是当前用户 $i$ 的推荐好友中共同好友数量并列最大的，如果是，把 $i$ 推荐好友数量加 1。如果 $i$ 和 $j$ 的共同好友数量甚至比之前找到的还要大，那么用户 $i$ 的推荐用户就变为了 $j$ 一人。

并且，在这些操作后，我们要把 $i$ 的共同好友数量记下来，故开一个数组 ans（大小也要开到`MAXN`的两倍喔）。

```cpp
for(int i=1;i<=tot;++i){
    int suggest_friends=0; // 推荐用户数量
    memset(flag,0,sizeof flag); // 清空一下
    for(int j=0;j<ship[i].size();++j) flag[ship[i][j]]=1; //  标记 i 和 j 好友
    for(int j=1;j<=tot;++j){
        if(i==j) continue; // 同一个人就跳过吧
        if(!flag[j]){ // 不为好友
            int both_friends=0; // 共同好友数量
            for(int k=0;k<ship[j].size();++k){
                if(flag[ship[j][k]]) both_friends++; // 查找 i 和 j 的共同好友
            }
            if(both_friends>ans[i]){ // i 和 j 的共同好友数量甚至比之前找到的还要大
                suggest_friends=1; // i 的推荐用户就变为了 j 一人。
                ans[i]=both_friends;
            }else if(both_friends==ans[i]) suggest_friends++; // 推荐好友数量加 1
        }
    }
    ans[i]=suggest_friends;// 设成最终的推荐用户数量
}
```

最后，我们把 ans 的第 $i$ 项设成最终的推荐用户数量。
最后的最后，我们循环输入的用户，输出名字和推荐用户数量（感谢出题人没有要求输出的顺序，否则还要麻烦）。

附上完整 AC 代码

```cpp
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<cstring>

#define il inline

const int MAXN = 5005;

using namespace std;

map<string,int> name;
map<string,int>::iterator iter;  
vector<int> ship[MAXN<<1];
bool flag[MAXN<<1];
int ans[MAXN];

int m;
int main(){
    std::ios::sync_with_stdio(false);
    cin>>m;
    string x,y;
    int ix,iy,tot=0;
    for(int i=1;i<=m;++i){
        cin>>x>>y;
        iter=name.find(x);
        if(iter!=name.end())  ix=iter->second;
        else name.insert(pair<string,int>(x,ix=++tot));
        iter=name.find(y);
        if(iter!=name.end())  iy=iter->second;
        else name.insert(pair<string,int>(y,iy=++tot));
        ship[ix].push_back(iy);
        ship[iy].push_back(ix);
    }
    cout<<tot<<endl;
    for(int i=1;i<=tot;++i){
        int suggest_friends=0;
        memset(flag,0,sizeof flag);
        for(int j=0;j<ship[i].size();++j) flag[ship[i][j]]=1;
        for(int j=1;j<=tot;++j){
            if(i==j) continue;
            if(!flag[j]){
                int both_friends=0;
                for(int k=0;k<ship[j].size();++k){
                    if(flag[ship[j][k]]) both_friends++;
                }
                if(both_friends>ans[i]){
                    suggest_friends=1;
                    ans[i]=both_friends;
                }else if(both_friends==ans[i]) suggest_friends++;
            }
        }
        ans[i]=suggest_friends;
    }
    for(iter=name.begin();iter!=name.end();++iter){
        cout<<iter->first<<" "<<ans[iter->second]<<endl;
    }
}
```



---

