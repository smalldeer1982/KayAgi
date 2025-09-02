# 题目信息

# [USACO23FEB] Cow-libi S

## 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

有人在 Farmer John 的 $G(1 \leq G \leq 10^5)$ 个私人花园里偷吃了庄稼！通过他的专业法医知识，Farmer John 确定了每个花园被偷吃的具体时间。他还发现，这些事件的罪魁祸首是一头单独的奶牛。

为了回应这些犯罪行为，Farmer John 的 $N(1 \leq N \leq 10^5)$ 头奶牛每头都提供了一个不在作案现场的证明（即“不在场证明”），表明奶牛在特定时间出现在特定位置。请帮助 Farmer John 判断这些“不在场证明”中哪些能够证明奶牛的清白。

如果一头奶牛无法在她的“不在场证明”位置与所有被偷吃地点之间往返，则可以确定这头奶牛是清白的。奶牛的移动速度为每单位时间 $1$ 单位距离。本题中提到的距离均为欧几里得距离。

## 样例 #1

### 输入

```
2 4
0 0 100
50 0 200
0 50 50
1000 1000 0
50 0 200
10 0 170```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

本题的核心在于判断奶牛的不在场证明是否成立，即奶牛是否无法在给定的时间内从一个犯罪地点移动到另一个犯罪地点。所有题解都采用了类似的思路：将犯罪事件按时间排序，然后通过二分查找找到与不在场证明时间最接近的两个犯罪事件，判断奶牛是否能在规定时间内完成移动。

### 所选高星题解

#### 1. 题解作者：快斗游鹿 (5星)
**关键亮点：**
- 思路清晰，详细解释了如何通过二分查找找到与不在场证明时间最接近的犯罪事件。
- 代码结构清晰，使用了 `double` 类型处理欧几里得距离，避免了精度问题。
- 特别处理了不在场证明时间早于或晚于所有犯罪事件的情况。

**核心代码：**
```cpp
int l=1,r=g,I=0;
while(l<=r){//二分
    int mid=(l+r)>>1;
    if(e[mid].t<=ttt)I=mid,l=mid+1;
    else r=mid-1;
}
double total;
if(!I){
    total=sqrt((double)(xxx-e[I+1].x)*(xxx-e[I+1].x)+(yyy-e[I+1].y)*(yyy-e[I+1].y));
    if(total>(e[I+1].t-ttt))ans++;
}
else if(I==g){
    total=sqrt((double)(xxx-e[I].x)*(xxx-e[I].x)+(yyy-e[I].y)*(yyy-e[I].y));
    if(total>(ttt-e[I].t))ans++;
}
else{
    int cnt=0;
    total=sqrt((double)(xxx-e[I+1].x)*(xxx-e[I+1].x)+(yyy-e[I+1].y)*(yyy-e[I+1].y));
    if(total>(e[I+1].t-ttt))cnt++;
    total=sqrt((double)(xxx-e[I].x)*(xxx-e[I].x)+(yyy-e[I].y)*(yyy-e[I].y));
    if(total>(ttt-e[I].t))cnt++;
    if(cnt)ans++;
}
```

#### 2. 题解作者：_3Zinc_ (4星)
**关键亮点：**
- 使用了 `lower_bound` 进行二分查找，代码简洁。
- 通过平方比较距离，避免了 `sqrt` 的精度问题。

**核心代码：**
```cpp
bool check(int i,ll t,ll x,ll y) {
    return (x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)<=(t-p[i].t)*(t-p[i].t);
}
int pos=lower_bound(tim+1,tim+1+n,t)-tim;
if(pos==1) ans+=check(pos,t,x,y)?1:0;
else if(pos-1==n) ans+=check(pos-1,t,x,y)?1:0;
else ans+=(check(pos,t,x,y)&&check(pos-1,t,x,y))?1:0;
```

#### 3. 题解作者：cff_0102 (4星)
**关键亮点：**
- 使用了 `tuple` 存储犯罪事件，代码简洁。
- 通过 `lower_bound` 进行二分查找，处理了不在场证明时间早于或晚于所有犯罪事件的情况。

**核心代码：**
```cpp
bool chk(tuple<int,int,int>b,int xa,int ya,int ta){
    int tb=get<0>(b),xb=get<1>(b),yb=get<2>(b);
    double dt=abs(ta-tb),dx=xa-xb,dy=ya-yb;
    double dis=sqrt(dx*dx+dy*dy);
    return dis<=dt;
}
int p=lower_bound(gs+1,gs+1+g,make_tuple(t,x,y))-gs-1;
ans+=(p==0||chk(gs[p],x,y,t))&&(p==g||chk(gs[p+1],x,y,t));
```

### 最优关键思路与技巧
1. **二分查找**：通过二分查找快速定位与不在场证明时间最接近的犯罪事件。
2. **距离计算**：通过平方比较距离，避免 `sqrt` 的精度问题。
3. **特判处理**：处理不在场证明时间早于或晚于所有犯罪事件的情况。

### 可拓展之处
- **类似题目**：可以扩展到其他需要判断时间与空间关系的题目，如路径规划、时间窗口等。
- **算法优化**：可以考虑使用更高效的数据结构或算法，如线段树、动态规划等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 个人心得总结
- **调试经历**：在处理精度问题时，使用平方比较距离可以有效避免 `sqrt` 带来的精度损失。
- **踩坑教训**：在处理边界情况时，需要特别注意不在场证明时间早于或晚于所有犯罪事件的情况。
- **顿悟感想**：通过二分查找可以快速定位与不在场证明时间最接近的犯罪事件，大大提高了算法的效率。

---
处理用时：34.46秒