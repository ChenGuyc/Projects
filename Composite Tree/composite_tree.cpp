/*******************************************************************************
* File Name: composite_tree.cpp	                       		             	   *
* Description: Definition functions of composite_tree                          *
* Developer: Guy Chen		                                                   *
* Date: 16.11.2020										                       *
*******************************************************************************/


#include <dirent.h> // opendir, readdir, closedir 
#include <iostream> // os
#include <cstring> // strncmp

#include "composite_tree.hpp"


#define BOLDBLUE "\033[1m\033[34m"
#define RESET "\033[0m"
#define BOLDGREEN "\033[1m\033[32m"


namespace hrd14
{

// class use as RAII for the functions opendir, closedir & readdir
class DirStream
{
public:
    explicit DirStream(const std::string& path);
    ~DirStream();
    DirStream(const DirStream& other) = delete;
    DirStream& operator=(const DirStream& other) = delete;

    bool operator!()
    {
        return (m_dir == nullptr);
    }

    struct dirent* ReadDir();

private:
    DIR* m_dir;
};

DirStream::DirStream(const std::string& path) : m_dir(opendir(path.c_str()))
{}

DirStream::~DirStream()
{
    closedir(m_dir);
}

struct dirent* DirStream::ReadDir()
{
    return (readdir(m_dir));
}



/************************** File Functions ************************************/

File::File(const std::string& name):m_name(name)
{}

const std::string File::GetName() const
{
    return(m_name);
} 

void File::Print(std::ostream& os, size_t level, std::string tree_branch) const
{
    (void)(level);
    (void)(tree_branch);

    os << this->m_name << std::endl;
}


std::shared_ptr<const File> File::Find(const std::string& name) const
{
    std::shared_ptr<const File> tmpFile;
    if (name != m_name)
    {
        return (nullptr);
    }
    return tmpFile;
}


/************************ Directory Functions *********************************/

Directory::Directory(const std::string& name) : File(name)
{}

void Directory::Add(std::shared_ptr<File> file)
{
    m_files.push_back(file);
}


std::string GetDirName(const std::string& path)
{
    size_t pathLen = path.length();

    size_t nameBegin = path.find_last_of('/', pathLen - 2);
    size_t nameEnd = path.find_last_of('/', pathLen) - 1;

    std::string dirName = path.substr(nameBegin + 1, nameEnd - nameBegin);

    return (dirName);
}


std::shared_ptr<Directory> Directory::Create(const std::string& path)
{   
    DirStream pDir (path.c_str());
    if(!pDir)
    {
        return(nullptr);
    }
 
    std::shared_ptr<Directory> RootDirectory(new Directory (GetDirName(path))); 
    struct dirent* entry  = pDir.ReadDir();
    while(entry != nullptr) 
    {
        if(!strncmp(entry->d_name,".",1) || (!strncmp(entry->d_name,"..",2)))
        {
            entry = pDir.ReadDir();
            continue;
        }  
      
        if (entry->d_type != DT_DIR)
        {
            RootDirectory->Add(std::make_shared<File> (entry->d_name));
        }
        else
        { 
            std::shared_ptr<Directory> CurrentDirectory(Create(path + "/" + entry->d_name)); 
            if(CurrentDirectory != nullptr)
            {
                RootDirectory->Add(CurrentDirectory); 
            }
        }
        
    entry = pDir.ReadDir();
    }
    return (RootDirectory);

}


void Directory::Print(std::ostream& os, size_t level, std::string tree_branch) const
{
    std::shared_ptr<Directory> ptr;
    for(size_t i = 0; i < m_files.size(); ++i)
    {
        if((level ==  m_files.size() - 1) || (i == m_files.size() - 1))
        {
            ptr = std::dynamic_pointer_cast<Directory>(m_files[i]);
            if(ptr)
            {
                os << tree_branch + "└── " << BOLDBLUE << m_files[i]->GetName() << RESET << std::endl;
                ptr->Print(os, level + 1, tree_branch + "    ");
            }
            else
            {
                os << tree_branch + "└── " << m_files[i]->GetName() << std::endl;
            }

        }
        else
        {
            ptr = std::dynamic_pointer_cast<Directory>(m_files[i]);
            if(ptr)
            {
                os << tree_branch + "├── " << BOLDBLUE << m_files[i]->GetName() << RESET << std::endl;
                ptr->Print(os, level, tree_branch + "│   ");
            }
            else
            {
                if(m_files[i]->GetName().length() > 4 &&
                        m_files[i]->GetName().substr(m_files[i]->GetName().length() - 4) == ".out")
                {
                    os << tree_branch + "├── " << BOLDGREEN << m_files[i]->GetName()<< RESET << std::endl;
                }
                else
                {
                    os << tree_branch + "├── " << m_files[i]->GetName() << std::endl;
                }
            }
        }
    }
}


std::shared_ptr<const File> Directory::Find(const std::string& name) const
{
   std::shared_ptr<const File> file(new File(""));

    
    if(name == this->GetName())
    {

        return shared_from_this();
    }

    size_t vecSize = this->m_files.size();

    for(size_t i = 0; i < vecSize; ++i)
    {
        std::shared_ptr<Directory> ptr = std::dynamic_pointer_cast<Directory>(m_files[i]);

        if(ptr != nullptr)
        {
 
            file = (ptr->Find(name));
        }
        if(ptr == nullptr)
        {
            if(name == m_files[i]->GetName())
            {
                return m_files[i];
            }
        }
    }

    return(file);
}
}




