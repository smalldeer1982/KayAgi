# 题目信息

# The Doctor Meets Vader (Easy)

## 题目描述

Heidi and Doctor Who hopped out of the TARDIS and found themselves at EPFL in 2018. They were surrounded by stormtroopers and Darth Vader was approaching. Miraculously, they managed to escape to a nearby rebel base but the Doctor was very confused. Heidi reminded him that last year's HC2 theme was Star Wars. Now he understood, and he's ready to face the evils of the Empire!

The rebels have $ s $ spaceships, each with a certain attacking power $ a $ .

They want to send their spaceships to destroy the empire bases and steal enough gold and supplies in order to keep the rebellion alive.

The empire has $ b $ bases, each with a certain defensive power $ d $ , and a certain amount of gold $ g $ .

A spaceship can attack all the bases which have a defensive power less than or equal to its attacking power.

If a spaceship attacks a base, it steals all the gold in that base.

The rebels are still undecided which spaceship to send out first, so they asked for the Doctor's help. They would like to know, for each spaceship, the maximum amount of gold it can steal.

## 说明/提示

The first spaceship can only attack the first base.

The second spaceship can attack the first and third bases.

The third spaceship can attack the first, second and third bases.

## 样例 #1

### 输入

```
5 4
1 3 5 2 4
0 1
4 2
2 8
9 4
```

### 输出

```
1 9 11 9 11
```

# AI分析结果

### 题目内容重写
**题目描述**

Heidi 和 Doctor Who 从 TARDIS 中跳出来，发现自己身处 2018 年的 EPFL。他们被风暴兵包围，达斯·维达正在逼近。奇迹般地，他们成功逃到了附近的叛军基地，但博士非常困惑。Heidi 提醒他，去年的 HC2 主题是《星球大战》。现在他明白了，准备面对帝国的邪恶！

叛军有 $s$ 艘宇宙飞船，每艘飞船都有一定的攻击力 $a$。

他们想派出飞船摧毁帝国基地，并窃取足够的黄金和物资以维持叛军的生存。

帝国有 $b$ 个基地，每个基地都有一定的防御力 $d$ 和一定量的黄金 $g$。

一艘宇宙飞船可以攻击所有防御力小于或等于其攻击力的基地。

如果一艘宇宙飞船攻击一个基地，它会窃取该基地的所有黄金。

叛军仍未决定先派出哪艘飞船，因此他们请求博士的帮助。他们想知道，对于每艘飞船，它能窃取的最大黄金量。

**说明/提示**

第一艘飞船只能攻击第一个基地。

第二艘飞船可以攻击第一个和第三个基地。

第三艘飞船可以攻击第一个、第二个和第三个基地。

**样例 #1**

输入：
```
5 4
1 3 5 2 4
0 1
4 2
2 8
9 4
```

输出：
```
1 9 11 9 11
```

### 算法分类
**二分 + 前缀和**

### 题解分析与结论
本题的核心思路是通过排序和前缀和优化查询过程。具体步骤如下：
1. **排序**：将基地按照防御力 $d$ 从小到大排序。
2. **前缀和**：计算每个基地的黄金前缀和，方便快速查询。
3. **二分查找**：对于每艘飞船的攻击力 $a_i$，使用二分查找找到第一个防御力大于 $a_i$ 的基地，其前一个基地的前缀和即为该飞船能窃取的最大黄金量。

### 高星题解推荐
#### 1. 作者：Withershine (赞：4)
**星级：★★★★★**
**关键亮点**：
- 详细解释了排序和前缀和的优化思路。
- 代码结构清晰，注释详细，易于理解。
- 使用了二分查找来优化查询效率。

**核心代码**：
```cpp
sort(str + 1, str + b + 1);
fr(i, 1, b) {
    q[i] = q[i - 1] + str[i].g;
}
fr(i, 1, s) {
    ll l = 1, r = b, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(str[mid].d <= a[i]) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%lld ", q[l - 1]);
}
```

#### 2. 作者：Ray_yi (赞：3)
**星级：★★★★☆**
**关键亮点**：
- 思路清晰，强调了排序和前缀和的必要性。
- 代码简洁，使用了结构体排序和二分查找。

**核心代码**：
```cpp
sort(k+1,k+b+1,cmp);
for(int i=1;i<=b;i++) kl[i]=kl[i-1]+k[i].g;
for(int i=1;i<=s;i++){
    int l=1,r=b,mid,ans=-1;
    while(l<=r){
        mid=(l+r)/2;
        if(k[mid].d<=a[i]){
            ans=max(kl[mid],ans);
            l=mid+1;
        }
        else r=mid-1; 
    }
    cout<<ans<<" ";
}
```

#### 3. 作者：Ybll_ (赞：3)
**星级：★★★★☆**
**关键亮点**：
- 详细解释了二分查找和前缀和的结合使用。
- 代码结构清晰，使用了结构体排序和前缀和优化。

**核心代码**：
```cpp
sort(b+1,b+1+m,cmp);
for(int i=1;i<=m;i++) b[i].g+=b[i-1].g;
for(int i=1;i<=n;i++){
    int l=1,r=m,mid,ans=0;
    while(l<=r){
        mid=l+r>>1;
        if(b[mid].d<=a[i]){
            ans=b[mid].g;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans<<" ";
}
```

### 最优关键思路
1. **排序**：将基地按照防御力从小到大排序，便于后续的二分查找。
2. **前缀和**：计算每个基地的黄金前缀和，方便快速查询。
3. **二分查找**：对于每艘飞船的攻击力 $a_i$，使用二分查找找到第一个防御力大于 $a_i$ 的基地，其前一个基地的前缀和即为该飞船能窃取的最大黄金量。

### 可拓展之处
- 类似的问题可以通过排序和前缀和来优化查询效率，如区间求和、区间最大值等问题。
- 二分查找可以应用于各种需要快速定位的场景，如查找第一个满足条件的元素。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得摘录
- **Withershine**：强调了暴力解法的时间复杂度问题，提醒读者不要尝试暴力解法。
- **Ray_yi**：提到排序和前缀和的结合使用是解决此类问题的关键。
- **Ybll_**：详细解释了二分查找和前缀和的结合使用，强调了代码的简洁性。

---
处理用时：40.98秒