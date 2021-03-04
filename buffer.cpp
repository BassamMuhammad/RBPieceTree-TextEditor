#include "buffer.hpp" 

Buffer::Buffer(string nText, vector<int> nLineFeeds){
    text = nText;
    lineFeeds = nLineFeeds;
}

string Buffer::getText(){
    return text;
}

vector<int> Buffer::getLineFeeds(){
    return lineFeeds;
}
