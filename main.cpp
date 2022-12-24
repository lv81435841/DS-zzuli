#include <bits/stdc++.h>
using namespace std;
struct User{
    int uid;
    int pass;
    long long number;
    int state=1; //ɾ����
};
struct food{
    string fid;
    string fname;
    string fprice;
};
struct shop{
    string type;
    long long sid;
    string name;
    string pass;
    double score;
    double avgPrice;
    string address;
    string number;
    struct food food[60];
    int foodi=0;
    string comment[30];
    int commenti=0;
    int state=1;
};
struct order{
    long long uid;
    string Sname;
    string time;
    int state=1;
};
struct distance{
    int sid1;
    string name1;
    int sid2;
    string name2;
    double distance;
};
struct distance dis;
struct User user[40];
struct order order[400];
struct shop shop[1000];
int useri,shopi,orderi,disi;
//����
void quick_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }

    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

unordered_map<string,int> shopmap;
//����תUnicode
std::string stringToUnicode(const std::string &str)
{
    std::string unicodeStr;
    size_t length = strlen(str.c_str())+1;
    // char * setlocale ( int category, const char * locale );
    // �������������õ������Ϣ�����õ�ǰ����ʹ�õı��ػ���Ϣ.���� locale ���ǿ��ַ��� ""�����ʹ��ϵͳ���������� locale
    // ˵��string�е��ַ������Ǳ���Ĭ���ַ�������GB�ַ���
    setlocale(LC_ALL,"");
    wchar_t wstr[length];
    mbstowcs(wstr, str.c_str(), length);
    char charUnicode[5];

    for (size_t i = 0; i < wcslen(wstr); i++) {
        memset(charUnicode, '\0', 5);
        sprintf(charUnicode, "%04x", wstr[i]);
        unicodeStr.append(charUnicode);
    }
    return unicodeStr;
}
//��������ϣ��
const int N=850;
int e[N],ne[N],h[N],idxx;
void insert(int x) {
    // c++������Ǹ��� ����ȡģҲ�Ǹ��� ���� ��N �� %N ��һ����һ������
    int k = (x % N + N) % N;
    e[idxx] = x;
    ne[idxx] = h[k];
    h[k] = idxx++;
}
bool find(int x) {
    //������ͬ���� Hash���� ��xӳ�䵽 �� 0-1e5 ֮�����
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (e[i] == x) {
            return true;
        }
    }
    return false;
}
typedef unsigned long long ULL;
const int P = 131;
ULL hh[N], p[N];
ULL get(int l, int r)
{
    ULL ull=hh[r] - hh[l - 1] * p[r - l + 1];
    return ull;
}
//���a�а���b������ �ַ�����ϣ
bool strhash(string a,string b){
    int n=a.size(),bb=b.size();
    p[0] = 1;
    for(int i=0;i<n;i++){
        p[i+1] = p[i]*P;
        hh[i+1] = hh[i]*P +(a[i]);      //ǰ׺���������ַ����Ĺ�ϣֵ
    }
    ULL bhash=0;
    for(int i=0;i<bb;i++){
        bhash = bhash*131+(b[i]);
    }
    for(int i=1;i<=n-bb+1;i++){
        if(get(i,i+bb-1)==bhash) return true;
    }
    return false;
}
void loadorder(){
    FILE *f=fopen("order.txt","r");
    if(f==NULL) {cout<<"�ļ�������"; return;}
    char tmp1[1000],tmp[1000];
    fgets(tmp,1000,f);
    while(fscanf(f,"%lld %s %s",&order[orderi].uid,tmp,tmp1)!=EOF){
        order[orderi].Sname=tmp; order[orderi].time=tmp1;
        orderi++;
    }
    cout<<"�������ݼ������\n";
    fclose(f);
}
void loadshop(){
    shop[shopi].name="֣���Ṥҵ��ѧ"; shop[shopi].sid=512324;
    shopmap["֣���Ṥҵ��ѧ\n"]=shopi;
    shopi++;
    FILE *f=fopen("shop.txt","r+");
    if(f==NULL) {cout<<"�ļ�������"; return;}
    char tmp[1000];
    while(fgets(tmp,1000,f)){
        string s=tmp;
        int d=s.find(":");
        shop[shopi].type=s.substr(d+2);
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].sid= stol(s.substr(d+2));
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].name= s.substr(d+2);
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].pass= s.substr(d+2);
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].score= stod(s.substr(d+2));
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].avgPrice= stod(s.substr(d+2));
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].address= s.substr(d+2);
        fgets(tmp,1024,f);
        s=tmp;
        d=s.find(":");
        shop[shopi].number= s.substr(d+2);
        char *b;
        char *tmp1;
        while( fgets(tmp,1024,f)!=NULL && tmp[0]=='f'){
            tmp1= strtok_s(tmp,",",&b);
            s=tmp1; d=s.find(":");
            shop[shopi].food[shop[shopi].foodi].fid=s.substr(d+2);
            tmp1= strtok_s(NULL, ",", &b);
            s=tmp1; d=s.find(":");
            shop[shopi].food[shop[shopi].foodi].fname=s.substr(d+2);
            tmp1= strtok_s(NULL, ",", &b);
            s=tmp1; d=s.find(":");
            shop[shopi].food[shop[shopi].foodi].fprice=s.substr(d+2);
            shop[shopi].foodi++;
        }
        char *end;
        int size;
        if(tmp[0]=='C'){
            s=tmp; d=s.find(":");
            shop[shopi].comment[shop[shopi].commenti]=s.substr(d+2);
            shop[shopi].commenti++;
        }else {
            for(size=0;tmp[size];size++){

            }
            shopi++;
            fseek(f,long(-size-1),SEEK_CUR);
            continue;
        }
        while( (end=fgets(tmp,1024,f))!=NULL && tmp[0]=='C'){
            s=tmp;
            d=s.find(":");
            shop[shopi].comment[shop[shopi].commenti]=s.substr(d+2);
            shop[shopi].commenti++;
        }
        if (end==NULL) break;
        shopmap[shop[shopi].name]=shopi;
        for(size=0;end[size];size++){
        }
        shopi++;
        fseek(f,long(-size-1),SEEK_CUR);
    }
    fclose(f);
}
void lookuser(int idx){
    cout<<"��ǰ�û�����Ϣ��"<<user[idx].uid<<' '<<user[idx].pass<<' '<<user[idx].number<<endl;
}
void changeuser(int idx){
    cout<<"�����������û��������ϵ��ʽ\n";
    cin>>user[idx].pass>>user[idx].number;
}
void deluser(int idx){
    user[idx].state=0;
    cout<<"ɾ���ɹ�\n";
    return;
}
int hashshopbyname(string name){
    if (shopmap.count(name+'\n')==1){
        return shopmap[(name+'\n')];
    }
    else {
        return -1;
    }
}
void lookorderuser(int idx){
    cout<<"���û��Ķ���Ϊ\n";
    for (int i = 0; i < orderi; ++i) {
        if(order[i].uid==user[idx].uid){
            cout<<order[i].Sname<<' '<<order[i].time<<endl;
        }
    }
}
void lookordershop(string name,int idx){
    cout<<"���û��ò͹ݵĶ���Ϊ\n";
    for (int i = 0; i < orderi; ++i) {
        if(order[i].uid==user[idx].uid && order[i].Sname==name){
            cout<<order[i].time<<endl;
        }
    }
}
void addorder(string name,int idx){

    if(shopmap.count(name+'\n')==1){
        cout<<"������Ԥ��ʱ��xx��xx��x��\n";
        string data;
        cin>>data;
        order[orderi].uid=user[idx].uid; order[orderi].Sname=name; order[orderi].time=data;
        orderi++;
        cout<<"��ӳɹ�\n";
    }else{
        cout<<"�޴��̼�\n";
    }

}
void shopre(){
    cout<<"���������͡���ɫ�ˡ����۹ؼ���\n";
    typedef pair<double,double> pii;
    vector<pii> v;
    string type,sp,com; cin>>type>>sp>>com;
    type+='\n';

    for (int i = 0; i < shopi; ++i) {
        int f=0;
        if(shop[i].type==type){
            v.push_back({shop[i].score,i});
            continue;
        }
        for (int j = 0; j < shop[i].foodi; ++j) {
            if (shop[i].food[j].fname==sp ){
                v.push_back({shop[i].score,i});
                f=1;
                break;
            }
        }
        if (f==1) continue;
        for (int j = 0; j < shop[i].commenti; ++j) {
            if(shop[i].comment[j].find(com)!=-1){
                v.push_back({shop[i].score,i});
                break;
            }
        }
    }
    sort(v.begin(),v.end());
    cout<<"�����򣬷���Ҫ����̼���:\n";
    for(int i=v.size()-1;i>=0;i--){
        int idx=v[i].second;
        cout<<"���֣�"<<shop[idx].name<<"��ַ��"<<shop[idx].address<<shop[idx].score<<endl;
    }
}
void loaduser(){
    FILE *f=fopen("user1.txt","r");
    if(f==NULL) {cout<<"�ļ�������"; return;}
    char tmp[100];
    fscanf(f,"%s",tmp);
    getchar();
    while(fscanf(f,"%d %d %lld",&user[useri].uid,&user[useri].pass,&user[useri].number)!=EOF){
        useri++;
    }
    cout<<"�û����ݼ������\n";
    fclose(f);
}
double g[N][N];
unordered_map<string,int> dismap;
void loaddis(){
    FILE *f=fopen("distance1.txt","r");
    if(f==NULL) {cout<<"�ļ�������"; return;}
    char tmp[1000];
    char tmp1[1000];
    memset(g, 0x7f, sizeof g);
    fscanf(f,"%s",tmp);
    while(fscanf(f,"%d %s %d %s %lf",&dis.sid1,tmp,&dis.sid2,tmp1,&dis.distance)!=EOF){
        dis.name1=tmp; dis.name2=tmp1;
        if(dismap.count(dis.name1)==0) {dismap[dis.name1]=disi; disi++;}
        if(dismap.count(dis.name2)==0) {dismap[dis.name2]=disi; disi++;}
        int a=dismap[dis.name1],b=dismap[dis.name2];
        g[a][b]=dis.distance;
//        if(dis[disi].sid1==0) {cout<<disi<<endl;
//            return;}
    }
    fclose(f);
    cout<<"�������ݼ������\n";
}
double dist[N];
bool st[N];
void sortdis(){
    memset(dist, 0x7f, sizeof dist);
    dist[0] = 0;
    for (int i = 0; i < disi-1 ; i ++ )
    {
        int t = -1;
        for (int j = 0; j < disi; j ++ )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        for (int j = 0; j < disi; j ++ )
            dist[j] = min(dist[j], dist[t] + g[t][j]);
        st[t] = true;
    }
}
void lookshop(int idx){
    cout<<"����:"<<shop[idx].type<<"���룺"<<shop[idx].pass<<"�˾����ѣ�"<<shop[idx].avgPrice<<endl<<"���֣�"<<shop[idx].name<<shop[idx].address<<"���֣�"<<shop[idx].score<<endl<<"�绰��"<<shop[idx].number<<endl;
}
void changeshop(int idx){
    cout<<"�������������͡����ơ����롢�˾����ѡ���ַ���绰\n";
    cin>>shop[idx].type>>shop[idx].name>>shop[idx].pass>>shop[idx].avgPrice>>shop[idx].address>>shop[idx].number;
    cout<<"�޸ĳɹ�\n";
}
void delshop(int idx){
    shop[idx].state=0;
    cout<<"ɾ���ɹ�\n";
}
void lookshoporder(int idx){
    cout<<"���̼ҵĶ���Ϊ\n";
    for (int i = 0; i < orderi; ++i) {
        if( (order[i].Sname+'\n') == shop[idx].name && order[i].state==1 ){
            cout<<order[i].uid<<' '<<order[i].time<<endl;
        }
    }
}
void lookuserorder(int idx,int uid){
    cout<<"���û��ڸ��̼ҵĶ���Ϊ\n";
    for (int i = 0; i < orderi; ++i) {
        if( (order[i].Sname+'\n') == shop[idx].name && uid==order[i].uid && order[i].state==1){
            cout<<order[i].time<<endl;
        }
    }
}
void delorder(int n,int idx){
    for (int i = 0; i < orderi; ++i) {
        if(n){
            if((order[i].Sname+'\n')==shop[idx].name&&order[i].state==1){
                n--;
                cout<<order[i].uid<<' '<<order[i].time<<endl;
                cout<<"�����Ѵ���\n";
                order[i].state=0;
            }
        }else{
            break;
        }
    }
    cout<<"�����������\n";
}
void saveshop(){
    FILE *f=fopen("shop.txt","wb");
    for (int i = 0; i < shopi; ++i) {
        if(shop[i].state==1)
        fwrite(&shop[i],sizeof(struct shop[0]),1,f);
    }
    cout<<"�̼����ݱ���ɹ�\n";
}
void saveorder(){
    FILE *f=fopen("order.txt","w+");
    fprintf(f,"%s","�û��˺� \t    �̼�����\t\t           Ԥ��ʱ��\n");
    int ii=0;
    while(ii++<orderi){
        if(order[ii].state==1)
            fprintf(f,"%d %s %s\n",order[ii].uid,order[ii].Sname.c_str(),order[ii].time.c_str());
    }
    fclose(f);
    cout<<"�����ѱ���\n";
    cout<<"���������ѱ���\n";
}
void saveuser(){
    FILE *f=fopen("user1.txt","w+");
    fprintf(f,"%s","�û��˺�������ϵ��ʽ\n");
    int ii=0;
    while(ii++<useri){
        if(user[ii].state==1)
            fprintf(f,"%d %d %lld\n",user[ii].uid,user[ii].pass,user[ii].number);
    }
    fclose(f);
    cout<<"�û������ѱ���\n";
}
void menu()
{
    printf("*************************************\n");
    printf("**********����������Ҫ�Ĺ���************\n");
    printf("*************1.�û���¼***************\n");
    printf("*************2.�̼ҵ�¼***************\n");
    printf("*************0.�˳�******************\n");
    printf("*********designed by ������**********\n");
    printf("************************************\n");
}
void usermenu(int idx){
    printf("*************************************\n");
    printf("**********����������Ҫ�Ĺ���************\n");
    printf("*************1.�鿴������Ϣ************\n");
    printf("*************2.�޸ĸ�����Ϣ************\n");
    printf("*************3.ע��������Ϣ************\n");
    printf("*************4.�͹ݲ�ѯ***************\n");
    printf("*************5.��ѯ�û�����Ԥ��*********\n");
    printf("*************6.��ѯĳ�͹ݵ�Ԥ��*********\n");
    printf("*************7.���Ԥ��***************\n");
    printf("*************8.�͹��Ƽ�***************\n");
    printf("*************0.�˳�******************\n");
    printf("*********designed by ������**********\n");
    printf("************************************\n");
    int op;
    loadshop();
    cout<<"�̼����ݼ������\n";
    loadorder();
    int t=0,tt=0;
    while(cin>>op){
        if(op==1){
            lookuser(idx);
        }else if(op==2){
            changeuser(idx);
        }else if(op==3){
            deluser(idx);
        }else if(op==4){
            cout<<"������͹ݵ�����\n";
            string name;cin>>name;
            if(shopmap.count(name+'\n')==-1) cout<<"�޴��̼�\n";
            else {
                int idx=shopmap[name+'\n'];
                cout<<shop[idx].type<<' '<<shop[idx].name<<' '<<shop[idx].score<<' '<<shop[idx].avgPrice<<' '<<shop[idx].address<<' '<<shop[idx].number<<endl;

                if(t==0){
                    loaddis();
                    t++;
                }
                idx=dismap[name];

                if (tt==0) {
                    sortdis();
                    tt++;
                }
                double dis=dist[idx];
                if(dis==-1) cout<<"�޷�����\n";
                else    cout<<"�����ǣ�"<<dis<<"��������"<<endl;
            }
        }else if(op==5){
            lookorderuser(idx);
        }else if(op==6){
            cout<<"������͹�����\n";
            string name; cin>>name;
            lookordershop(name,idx);
        }else if(op==7){
            cout<<"������͹�����\n";
            string name; cin>>name;
            addorder(name,idx);
        }else if(op==8){
            shopre();
        }else if(op==0){
//          saveuser();
//          saveorder();
            exit(0);
        }else{
            cout<<"����������";
        }
    }
}
void load(){
    insert(1);
    find(1);
    strhash("1","1");
}
void shopmenu(int idx){
    printf("*************************************\n");
    printf("**********����������Ҫ�Ĺ���************\n");
    printf("*************1.��ѯ�͹���Ϣ************\n");
    printf("*************2.�޸Ĳ͹���Ϣ************\n");
    printf("*************3.ע���͹���Ϣ************\n");
    printf("*************4.��ѯ�͹�����Ԥ��********\n");
    printf("*************5.��ѯĳ�û�Ԥ��**********\n");
    printf("*************6.����Ԥ��***************\n");
    printf("*************0.�˳�******************\n");
    printf("*********designed by ������**********\n");
    printf("************************************\n");
    int op;
    loadorder();
    while(cin>>op){
        if(op==1){
            lookshop(idx);
        }else if(op==2){
            changeshop(idx);
        }else if(op==3){
            delshop(idx);
        }else if(op==4){
            lookshoporder(idx);
        }else if(op==5){
            cout<<"�������û���id\n";
            int uid; cin>>uid;
            lookuserorder(idx,uid);
        }else if(op==6){
            cout<<"������Ҫ����Ķ�����:";
            int n;cin>>n;
            delorder(n,idx);
        }else if(op==0){
//          saveshop();
//          saveorder();
            exit(0);
        }else{
            cout<<"����������\n";
        }
    }
}
void LoginUser(){
    loaduser();
    cout<<"**************************************\n";
    cout<<"***********�����˺ź������밴1***********\n";
    cout<<"************�����û�ע���밴2************\n";
    cout<<"*********designed by ������************\n";
    int op; cin>>op;
    if(op==1){
        int id,f=0; int pass;
        cout<<"�������˺ź����룺\n";
        cin>>id>>pass;
        for(int i=0;i<useri;i++){
            if (user[i].uid==id && user[i].pass==pass) {
                f=1;
                id=i;
            }
        }
        if(f==1){
            cout<<"��¼�ɹ�\n";
            usermenu(id);
        } else{
            cout<<"���޴���\n";
        }
    }else if (op==2){
        cout<<"�������˺š����롢��ϵ��ʽ\n";
        cin>>user[useri].uid>>user[useri].pass>>user[useri].number;
        useri++;
        cout<<"ע��ɹ�,\n";
        LoginUser();
    }else{
        cout<<"�������,������ҳ��\n";
    }
}
void LoginShop(){
    loadshop();
    cout<<"�̼����ݼ������\n";
    cout<<"**************************************\n";
    cout<<"***********�������˺ź�����***********\n";
    cout<<"*********designed by ������************\n";

    long long id,f=0; long long pass; cin>>id>>pass;
    for(int i=0;i<shopi;i++){
        if (shop[i].sid==id&& stol(shop[i].pass)==pass) {
            f=1;
            id=i;
        }
    }
    if(f==1){
        cout<<"��¼�ɹ�\n";
        shopmenu(id);
    }else{
        cout<<"�޴��̼�\n";
    }

}

int main()
{
    load();
    int op;
    do{
        menu();
        cin>>op;
        switch (op)
        {
            case 1:
                LoginUser();
                break;
            case 2:
                LoginShop();
                break;
            case 0:
                printf("�˳��ɹ�!\n");
                break;
            default:
                printf("ѡ�����,������ѡ��!\n");
                break;
        }
    }while (op!=0);
    return 0;
}