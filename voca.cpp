#include "voca.h"

// 일시정지
void pause(){
    string tmp;
    cout<<"아무거나 입력하세요."<<endl;
    cin>>tmp;
    cin.ignore();
}

// 생성자
voca::voca(){
    file_path = "./voca/";
    dont_know_path = "./voca/dontknow.txt";
}

// 단어 순서 섞기
void voca::shuffle(){
    int shuffle_n = english.size();
    srand((unsigned int)time(NULL));
    while(shuffle_n--){
        int rand_num = rand()%english.size();
        pair<string,string> tmp;
        tmp = english.at(rand_num);
        english.erase(english.begin() + rand_num);
        english.push_back(tmp);
    }
}

// 모르는 단어 저장
void voca::write_dont_know_file(int index){
    ofstream dataFile;
    dataFile.open(dont_know_path,ios::app);
    pair<string,string> dont_know_word = english.at(index);
    dataFile << dont_know_word.first << ":" << dont_know_word.second << endl;
    dataFile.close();
}

// 단어 암기 테스트
void voca::test(){
    for(int i=0;i<english.size();++i){
        pair<string,string> word;
        word = english.at(i);
        cout<<word.first<<endl;
        cout<<"알면 = 1, 모르면 = 2, 뜻 확인 = 3, 뒤로가기 = 4 그만 = 5 입력 : ";
        char ins;
        cin>> ins;
        cin.ignore();
        

        if(ins=='3'){
            cout<<"뜻 = "<<english.at(i).second<<endl<<endl;
            --i;
            continue;
        }
        if(ins=='4'){
            i-=2;
            continue;
        }
        if(ins=='5') break;
        
        if(file_path == "./voca/dontkonw.txt"){
            if(ins == '1'){
                cout<<english.at(i).first<<" 못 외운 단어장에서 삭제"<<endl;
                english.erase(english.begin() + i);
            }else{
                cout<<"뜻 = "<<english.at(i).second<<endl;
            }
        }
        else if(ins == '1'){
            continue;
        }else if(ins == '2'){
            cout<<"뜻 = "<<english.at(i).second<<endl;
            write_dont_know_file(i);
        }else{
            cout<<"잘못 입력했습니다."<<endl;
            --i;
            continue;
        }
    }
}



// 단어 입력
void voca::insert(string word,string meaning){
    pair<string,string> english_word;
    english_word.first = word;
    english_word.second = meaning;
    english.push_back(english_word);
}

// 마지막 단어 삭제
void voca::delete_end(){
    english.pop_back();
}

// 단어 뜻 출력
void voca::print(){
    for(int i=0;i<english.size();++i){
        pair<string,string> word;
        word = english.at(i);
        if(word.first.length() < 12){
            cout<<i+1<<". "<<word.first<<"\t\t"<<word.second<<endl;
        }else{
            cout<<i+1<<". "<<word.first<<"\t"<<word.second<<endl;
        }
    }
}

// 영어 단어만 출력
void voca::print_word(){
    for(int i=0;i<english.size();++i){
        pair<string,string> word;
        word = english.at(i);
        cout<<i+1<<". "<<word.first<<endl;
    }
}

// 메뉴 출력
void voca::print_menu(){
    
    cout<< "**********************************" << endl;
    cout<< "  기본 : 단어 1회, 뜻 1회 입력" << endl;
    cout<< "  숫자 1 입력 : 영어 단어만 출력" << endl;
    cout<< "  숫자 2 입력 : 단어 뜻 모두 출력" << endl;
    cout<< "  숫자 3 입력 : 전체 단어 삭제" << endl;
    cout<< "  숫자 4 입력 : 마지막 단어 삭제" << endl;
    cout<< "  숫자 5 입력 : 단어 순서 섞기" << endl;
    cout<< "  숫자 6 입력 : 단어 암기 테스트" << endl;
    cout<< "  숫자 7 종료 : 프로그램 종료" << endl;
    cout<< "**********************************" << endl;
}

// 단어장 선택
void voca::decide_voca(){
    cout<<"** 외울 voca를 입력하세요 ( ex = d20 ) ( sample = d19 and d20 )"<<endl;
    cout<<"** 못 외운 단어 모음 단어장 = dontknow"<<endl;
    cout<<"** 새로운 voca를 만들려면 원하는 voca 이름을 입력하세요 ( ex = myvoca )"<<endl;

    string ins;
    cin>>ins;
    voca_name = ins;
    cin.ignore();
}

// 단어 전체 삭제
void voca::clear(){
    english.clear();
}

// 현재 단어장 저장
void voca::write_text(){
    ofstream writeFile(file_path.data());
    if(writeFile.is_open()){
        for(int i=0;i<english.size();++i){
            writeFile << english.at(i).first << ":" << english.at(i).second << endl;
        }
        writeFile.close();
    }
    
}

// 단어장 불러오기
void voca::load_text(){
    file_path += voca_name + ".txt";
    ifstream loadFile(file_path.data());
    if(loadFile.is_open()){
        string line;
        while(getline(loadFile,line)){
            stringstream ss(line);
            pair<string,string> eng;
            getline(ss,eng.first,':');
            getline(ss,eng.second,':');
            english.push_back(eng);
        }
        loadFile.close();
    }
}

// 단어장 프로그램 시작
void voca::start_eng(){
    bool flag = true;
    pair<string,string> ins_eng;
    decide_voca();
    load_text();
    while(1){
        print_menu();
        if(flag){
            cout<<"옵션 혹은 단어를 입력해주세요"<<endl;
        }else{
            cout<<"옵션 혹은 뜻을 입력해주세요"<<endl;
        }
        string ins;
        getline(cin,ins);
        fflush(stdin);
        if(0<=ins[0]-'0'&&ins[0]-'0'<10){
            switch (ins[0]-'0')
            {
                case 1:
                    print_word();
                    pause();
                    break;
                case 2:
                    print();
                    pause();
                    break;
                case 3:
                    clear();
                    break;
                case 4:
                    delete_end();
                    break;
                case 5:
                    shuffle();
                    break;
                case 6:
                    test();
                    break;
                case 7:
                    write_text();
                    return;
                default:
                    cout<<"잘못된 숫자입니다. 다시 입력하세요"<<endl;
                    break;
            }
            flag = true;
        }else{
            if(flag){
                ins_eng.first = ins;
                flag = false;
                cout<<"단어가 입력되었습니다."<<endl;
            }else{
                ins_eng.second = ins;
                english.push_back(ins_eng);
                flag = true;
                cout<<"뜻이 입력되었습니다."<<endl;
            }
        }
    }
}