# 题目信息

# Santa Claus and Keyboard Check

## 题目描述

# 题义翻译
圣诞老人拆开、清洁了他的键盘，但是在将所有的按键安好后，他发现一些按键的位置发生
了两两交换！于是，圣诞老人猜测对于键盘上的每一个按键，要么在它本来正确的位置，
要么与另一个按键交换了位置。  为了验证他的猜想，他决定只根据正确的按键位置打出他
最爱的文字。现给出圣诞老人要打出的字符串 *s*，和他实际敲出的字符串 *t*,请你确定
哪几组字母发生了两两交换（即每对交换位置的字母不应出现在其他字母对中）

## 样例 #1

### 输入

```
helloworld
ehoolwlroz
```

### 输出

```
3
h e
l o
d z
```

## 样例 #2

### 输入

```
hastalavistababy
hastalavistababy
```

### 输出

```
0
```

## 样例 #3

### 输入

```
merrychristmas
christmasmerry
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
圣诞老人拆开、清洁了他的键盘，但是在将所有的按键安好后，他发现一些按键的位置发生了两两交换！于是，圣诞老人猜测对于键盘上的每一个按键，要么在它本来正确的位置，要么与另一个按键交换了位置。  为了验证他的猜想，他决定只根据正确的按键位置打出他最爱的文字。现给出圣诞老人要打出的字符串 *s*，和他实际敲出的字符串 *t*，请你确定哪几组字母发生了两两交换（即每对交换位置的字母不应出现在其他字母对中）

### 算法分类
模拟

### 综合分析与结论
这几道题解核心思路相近，都是通过建立字符之间的对应关系来判断是否存在合法的两两交换，若出现一个字符对应多个不同字符的情况则判定无解，最后统计并输出交换的字符对。

- **思路对比**：
    - Patients、Noby_Glds 和 Zaku 的题解都是通过数组或 `map` 来记录字符的对应关系，直接判断是否符合两两交换的规则。
    - Ninelife_Cat 的题解将问题转换为图论中的连通块问题，通过判断连通块元素个数是否大于 2 来确定是否合法。

- **算法要点对比**：
    - Patients 和 Noby_Glds 用数组存储对应关系，Noby_Glds 还额外用数组存储要输出的字符对。
    - Zaku 用 `map` 记录对应关系，按字典序输出答案。
    - Ninelife_Cat 用 `map` 存对应关系，用 `vector` 存储答案，最后去除自环。

- **难点对比**：
    - 各题解都需要处理好判断无解的情况，不同的判断顺序可能导致结果错误。
    - Ninelife_Cat 的题解需要将问题转换为图论模型，对思维能力要求较高。

### 题解列表
- **Patients（4星）**：
    - **关键亮点**：思路清晰，对不同情况进行了详细的分类讨论，代码注释丰富，易于理解。
    - **个人心得**：提到判断无解的顺序一定不能错，否则会出错。
- **Noby_Glds（4星）**：
    - **关键亮点**：代码简洁，运行速度较快，思路直接。
    - **个人心得**：表示这道题很坑，交了五次才通过。
- **Ninelife_Cat（4星）**：
    - **关键亮点**：将问题转换为图论模型，思维独特，代码实现巧妙。

### 重点代码
#### Patients
```cpp
string s,t;
char h[27];
bool vis[27];
signed main()
{
    cin>>s>>t;
    int ans=0;
    for(int i=0;i<=26;i++) h[i]=' ';
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==t[i])
            if((h[s[i]-'a']!=t[i] || h[t[i]-'a']!=s[i]) && !(h[s[i]-'a']==' ' && h[t[i]-'a']==' ')) {cout<<-1;return 0;} 
            else h[s[i]-'a']=t[i];
        else if(h[s[i]-'a']==' ' && h[t[i]-'a']==' ')
        {
            h[s[i]-'a']=t[i],h[t[i]-'a']=s[i],ans++;
        }
        else if(h[s[i]-'a']!=t[i] || h[t[i]-'a']!=s[i]) {cout<<-1;return 0;} 
    }
    cout<<ans<<'\n';
    for(int i=0;i<s.length();i++)
    {
        if(!vis[s[i]-'a'] && s[i]!=t[i])
        {
            vis[s[i]-'a']=vis[t[i]-'a']=1;
            cout<<s[i]<<' '<<t[i]<<'\n';
        }
    }
    return 0;
}
```
**核心思想**：用数组 `h` 记录字符的对应关系，通过分类讨论判断是否合法，最后输出结果。

#### Noby_Glds
```cpp
string a,b;
int vis[150],kw[1500],tot;
int main(){
    cin>>a>>b;
    for(int i=0;i<a.size();i++){
        if(vis[a[i]]==0&&vis[b[i]]==0){
            vis[a[i]]=b[i];
            vis[b[i]]=a[i];
            if(a[i]!=b[i]) kw[++tot]=a[i];
            continue;
        }
        if((vis[a[i]]!=b[i]||vis[b[i]]!=a[i])){
            cout<<"-1";
            return 0;
        }
    }
    cout<<tot<<endl;
    for(int i=1;i<=tot;i++){
        char x,y;
        x=kw[i];
        y=vis[x];
        cout<<x<<" "<<y<<endl;
    }
    return 0;
}
```
**核心思想**：用数组 `vis` 记录对应关系，`kw` 数组存储要输出的字符对，遍历判断是否合法，最后输出结果。

#### Ninelife_Cat
```cpp
string s,t;
int len,siz;
vector<pair<char,char> > ans;
map<char,char> a;
signed main()
{
    cin>>s>>t;len=s.size();
    for(ri int i=0;i<len;++i)
    {
        if(a[s[i]]&&a[s[i]]!=t[i]) return cout<<-1,0;
        if(a[t[i]]&&a[t[i]]!=s[i]) return cout<<-1,0;
        if(!a[s[i]]&&!a[t[i]]) ans.pb(mp(s[i],t[i])),a[s[i]]=t[i],a[t[i]]=s[i];
    }
    siz=ans.size();
    for(ri int i=0;i<ans.size();++i)
        if(ans[i].fir==ans[i].sec) --siz;
    cout<<siz<<endl;
    for(ri int i=0;i<ans.size();++i)
        if(ans[i].fir!=ans[i].sec) cout<<ans[i].fir<<" "<<ans[i].sec<<endl;
    return 0;
}
```
**核心思想**：用 `map` 存储对应关系，`vector` 存储答案，将问题转换为图论模型，判断连通块元素个数，最后去除自环并输出结果。

### 最优关键思路或技巧
- 建立字符之间的对应关系，通过判断对应关系是否合法来确定是否存在两两交换。
- 可以将问题转换为图论模型，利用连通块的性质进行判断，使问题更直观。

### 拓展思路
同类型题可能会有更多复杂的条件，如多个字符的循环交换、交换次数的限制等。可以继续使用模拟或图论的方法，根据具体条件进行调整。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)

---
处理用时：46.34秒