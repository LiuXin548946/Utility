//retry_count指定网络操作重试的次数，0表示只尝试一次
//retry_sleep重试间隔，单位毫秒
bool callWithRetry(unsigned int retry_count, unsigned int retry_sleep_millseconds, std::function<bool()> call){
    for(unsigned int i=0; i < retry_count; i++){
        if(call()){
            return true;
        }
        usleep(retry_sleep_millseconds * 1000);
    }
    return false;
}
//eg
if(!callWithRetry(retry_count, retry_sleep_millsecods, [&]()->bool{
    return LoadImage(image_url, output, img_size, retry_sleep_millsecods);
})){
    err_msg = err_msg_download_pic_fail;
    err_code = CppProcess::kImgDownloadFail;
    LOG(ERROR) << err_msg;
}
