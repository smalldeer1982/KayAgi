# 题目信息

# [NEERC 2016] Hard Refactoring

## 题目描述

对于一个变量 $x$，给出一些约束条件，形如 $x \geq a$，$x \le a$ 
这些约束条件之间用```||```连接，然后你需要将这些约束条件简化，最后输出简化后的约束条件。

## 说明/提示

对于所有在这一题中出现的数字（包括 $x$），都$\ge -32768$（$-2^{15}$） 且 $\le 32767 $（$2^{15}-1$）。

## 样例 #1

### 输入

```
x >= 5 && x <= 10 ||
x >= 7 && x <= 20 ||
x <= 2 ||
x >= 21 && x <= 25 ||
x >= 8 && x <= 10 ||
x >= 100```

### 输出

```
x <= 2 ||
x >= 5 && x <= 25 ||
x >= 100```

# AI分析结果

### 综合分析与结论
这些题解核心都是将输入的不等式约束转化为区间，再合并区间以最简形式输出。主要思路有排序合并、差分、线段树、树状数组这几种。排序合并思路直观，实现简单；差分和树状数组适合处理区间修改和单点查询；线段树则适用于复杂的区间操作。

### 所选题解
- **作者：peixiaorui（5星）**
    - **关键亮点**：思路清晰，代码简洁易读，详细处理了输入输出和区间合并的边界情况。
    - **核心代码**：
```cpp
struct node{
    int le,ri;
};
bool cmp(node a,node b){return a.le<b.le;}
vector<node> res,ans;
// 处理输入
while(1){
    string xxx,op;int num;
    cin>>xxx>>op>>num;
    int le=-inf,ri=inf-1;
    if(op=="<=")ri=num;
    else le=num;
    if(!(cin>>xxx)){res.push_back({le,ri});break;}
    if(xxx=="&&"){
        cin>>xxx>>op>>num;
        ri=num;
        if(le>ri)wrong_cnt++;
        if(!(cin>>xxx)){res.push_back({le,ri});break;}
    }
    res.push_back({le,ri});
}
// 排序并合并区间
sort(res.begin(),res.end(),cmp);
int le=res[0].le,ri=res[0].ri;
for(int i=1;i<res.size();i++){
    if(res[i].le>res[i].ri)continue;
    if(res[i].le>ri+1){
        ans.push_back({le,ri});
        le=res[i].le,ri=res[i].ri;
        continue;
    }
    ri=max(ri,res[i].ri);
}
ans.push_back({le,ri});
```
- **作者：LLqm_rYZ（4星）**
    - **关键亮点**：采用差分思想，思路新颖，对负数处理和边界情况考虑周全。
    - **核心代码**：
```cpp
// 输入处理
while(getline(cin,str)){
    len=str.size(),lef=-INF,rig=INF-1;
    for(int i=0;i<len;i++)
        if(str[i]=='>') lef=get(i);
        else if(str[i]=='<') rig=get(i);
    if(lef>rig)continue;
    d[lef+INF+1]++,d[rig+INF+2]--;
}
// 前缀和与计数
for(int i=1;i<=2*INF;i++){
    d[i]+=d[i-1];
    if(d[i])cnt++;
}
// 输出处理
lef=1,rig=INF+INF;
for(int i=1;i<=2*INF+1;i++){
    if(!d[i-1]&&d[i]) lef=i;
    if(d[i-1]&&!d[i]){
        rig=i-1;
        if(ed)cout<<"||\n";
        if(lef==1) cout<<"x <= "<<rig-INF-1<<" ";
        else cout<<"x >= "<<lef-INF-1<<" && x <= "<<rig-INF-1<<" ";
        ed=1,lef=1,rig=INF+INF;
    }
}
```
- **作者：biology（4星）**
    - **关键亮点**：贪心思路明确，代码实现规范，对不合法区间和边界输出处理得当。
    - **核心代码**：
```cpp
struct exp{
    int st,en;
    bool operator<(exp e2)const{
        if(st!=e2.st) return st<e2.st;
        return en<e2.en;
    }
}ex[1000];
// 输入处理
while(1){
    gets(s);
    flag=op=num=0,len=strlen(s),ex[c].st=-32768,ex[c].en=32767;
    for(int i=0;i<len;i++){
        if(s[i]=='<') flag=false;
        if(s[i]=='>') flag=true;
        if(s[i]=='-') ng=true;
        if(isdigit(s[i])) num=num*10+(s[i]-'0')*(ng?-1:1),op=true;
        if(i&&!isdigit(s[i])&&isdigit(s[i-1])){
            if(flag) ex[c].st=num,ng=num=0;
            else ex[c].en=num,ng=num=0;
            op=false;
        }
    }
    if(op){
        if(flag) ex[c].st=num,num=0;
        else ex[c].en=num,num=0;
    }
    c++;
    if(s[len-1]!='|') break;
}
// 排序与合并
sort(ex,ex+c);
flag=op=false;
for(int i=0;i<c;i++){
    if(i&&ben+1<ex[i].st){
        flag=false;
        if(bst<=ben){
            print(bst,ben,op);
            op=true;
        }
    }
    if(!flag){
        bst=ex[i].st,flag=true;
    }
    ben=max(ben,ex[i].en);
}
if(bst<=ben) print(bst,ben,op);
else if(!op) printf("false");
```

### 最优关键思路或技巧
- **排序合并**：将区间按左端点排序，遍历合并相交区间，简单直观，适用于大多数区间合并问题。
- **差分**：通过对差分数组操作实现区间修改，最后前缀和还原原数组，可高效处理区间修改和单点查询。
- **负数处理**：整体平移数据，避免负数带来的数组下标问题。

### 可拓展之处
同类型题如区间覆盖、区间合并、区间查询等问题，都可使用排序合并、差分、线段树、树状数组等方法解决。

### 洛谷相似题目推荐
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)
- [P5568 [SDOI2008] 校门外的区间](https://www.luogu.com.cn/problem/P5568)

### 个人心得摘录与总结
部分题解提到本题细节多易抓狂，如输入输出格式处理、负数处理、不合法区间特判等。提醒我们在解题时要仔细考虑边界情况和特殊情况，避免因细节问题出错。 

---
处理用时：47.78秒