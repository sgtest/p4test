/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * fileio.h - subclasses of FileSys that actually operate on files
 *
 * Classes defined:
 *
 *	FileIO - hulk that acts on files, but not content
 *	FileIOBinary - raw binary files (unbuffered)
 *	FileIOBuffer - buffered files: raw/cr/crlf
 *	FileIOUnicode - buffered files: raw/cr/crlf w/UTF8 translation
 *	FileIOUTF16 - buffered files: raw/cr/crlf w/UTF8vs16 translation
 *	FileIOEmpty - empty file (simulates an empty file)
 *	FileIOAppend - text file in append only mode (write only)
 *	FileIOGzip - compressed binary file
 *	FileIOGunzip - binary file via compressed stream
 *	FileIOSymlink - symbolic links (UNIX only!)
 *	FileIOResource - Macintosh resource fork
 *	FileIOApple - apple double format or native on Macintosh
 */

class FileIO : public FileSys {

    public:
			FileIO();

	virtual int	Stat();
	virtual int     GetOwner();
	virtual int	StatModTime();
	virtual bool	HasOnlyPerm( FilePerm perms );
	virtual void	Truncate( Error *e );
	virtual void	Chmod( FilePerm perms, Error *e );
	virtual void	ChmodTime( Error *e );
	virtual void	ChmodTime( int modTime, Error *e );
	virtual void	Unlink( Error *e );
	virtual void	Rename( FileSys *target, Error *e );
	// No NT implementation of Readlink, will return error
	virtual int	Readlink( StrBuf &linkPath, Error *e );
	// No NT implementation of Readlink, will return error
	virtual int	Writelink( const StrPtr &linkPath, Error *e );


# ifdef OS_NT
	static wchar_t	*UnicodeName( const char *fname, int flen );
# endif

} ;

class FileIOBinary : public FileIO {

    public:
			FileIOBinary() { fd = -1; tellpos = 0; };
	virtual   	~FileIOBinary();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

	virtual int	GetFd() { return fd; }
	virtual offL_t	GetSize();
	virtual void	Seek( offL_t offset, Error *e );
	virtual offL_t	Tell();

    protected:

	int		fd;
	offL_t		tellpos;

	static const struct OpenMode {
		const char *modeName;
		int bflags;	// binary mode
		int aflags;	// append text mode
		int standard;
	} openModes[3];

} ;

class FileIOBuffer : public FileIOBinary {

    public:
			FileIOBuffer( LineType lineType ) : 
			    rcv( 0 ), snd( 0 ),
			    lineType( lineType ),
			    iobuf( BufferSize() )
	                {}

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );
	virtual void	Seek( offL_t offset, Error *e );
	virtual offL_t	Tell();
	virtual int	ReadLine( StrBuf *buf, Error *e );
	virtual void	SetBufferSize( size_t l );

    protected:
	char		*ptr;
	int		rcv;
	int		snd;

	LineType	lineType;
	StrFixed	iobuf;

	virtual void	FlushBuffer( Error * );
	virtual void	FillBuffer( Error * );
} ;

class FileIOUnicode : public FileIOBuffer {
    public:
			FileIOUnicode( LineType lineType ) : 
			    FileIOBuffer( lineType ),
			    trans( NULL ),
			    tbuf( BufferSize() ),
			    tsz( 0 )
	                {}

	virtual void	Close( Error * );
	virtual void	Translator( CharSetCvt * );

    protected:
	CharSetCvt	*trans;
	StrFixed	tbuf;
	int		tsz;

	virtual void	FlushBuffer( Error * );
	virtual void	FillBuffer( Error * );
} ;

class FileIOUTF16 : public FileIOUnicode {
    public:
	FileIOUTF16( LineType lineType );

	virtual void	Set( const StrPtr &name );
	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Close( Error *e );
	virtual void	Translator( CharSetCvt * );
};

class FileIOAppend : public FileIOBuffer {

    public:

	FileIOAppend() : FileIOBuffer( LineTypeLocal ) {} ;
	virtual         ~FileIOAppend();

	virtual void    Close( Error *e );
	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );

	// for atomic filesize
	virtual offL_t	GetSize();

	// Copies on Windows.
	// Locks, renames, and removes write on UNIX.

	virtual void	Rename( FileSys *target, Error *e );

} ;

class Gzip;

class FileIOGzip : public FileIOBinary {

    public:
			FileIOGzip() : gzip(0), iobuf( BufferSize() ) {}
			~FileIOGzip();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

    private:
	Gzip		*gzip;
	StrFixed	iobuf;

} ;

class FileIOGunzip : public FileIOBinary {

    public:
			FileIOGunzip() : gzip(0), iobuf( BufferSize() ) {}
			~FileIOGunzip();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

    private:
	Gzip		*gzip;
	StrFixed	iobuf;

} ;

class FileIOEmpty : public FileSys {

    public:
			FileIOEmpty() {}
			~FileIOEmpty() {}

	virtual int	Stat() { return FSF_EMPTY; }
	virtual int	StatModTime() { return 0; }
	virtual void	Truncate( Error *e ) {}
	virtual void	Chmod( FilePerm perms, Error *e ) {}
	virtual void	ChmodTime( Error *e ) {}
	virtual void	ChmodTime( int modTime, Error *e ) {}
	virtual void	Unlink( Error *e ) {}
	virtual void	Rename( FileSys *target, Error *e ) {}

	virtual void	Open( FileOpenMode mode, Error *e ) {};
	virtual void	Write( const char *buf, int len, Error *e ) {}
	virtual int	Read( char *buf, int len, Error *e ) { return 0; }
	virtual void	Close( Error *e ) {}

	virtual int	GetFd() { return -1; }
	virtual offL_t	GetSize() { return 0; }
	virtual void	Seek( offL_t offset, Error * ) {}
} ;

# ifdef HAVE_SYMLINKS

class FileIOSymlink : public FileIO {

    public:
			~FileIOSymlink();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

	virtual int	StatModTime();
	virtual void	Truncate( Error *e );
	virtual void	Chmod( FilePerm perms, Error *e );
	virtual void	ChmodTime( int modTime, Error *e );

    private:
	StrBuf		value;
	int		offset;

} ;

# else

class FileIOSymlink : public FileIOBinary { } ;

# endif // HAVE_SYMLINKS


class AppleForkSplit;
class AppleForkCombine;
class DataFork;

# if !defined ( OS_MACOSX )

class FileIOResource : public FileIOBinary { } ;

class FileIOApple : public FileIO {

    public:

			FileIOApple();
			~FileIOApple();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

    private:

	// Split, and combine AppleSingle format

	AppleForkSplit 		*split;
	AppleForkCombine	*combine;
	DataFork		*dataFork;


	// Access to underlying data and %header files.

	FileIO		*data;

    // NON-MAC SPECIFIC
    //
    public:

	virtual bool    HasOnlyPerm( FilePerm perms );
	virtual int	Stat();
	virtual void	Set( const StrPtr &s );

	virtual int	StatModTime();
	virtual void	Truncate( Error *e );
	virtual void	Chmod( FilePerm perms, Error *e );
	virtual void	ChmodTime( int modTime, Error *e );
	virtual void	Unlink( Error *e );
	virtual void	Rename( FileSys *target, Error *e );

    private:
	FileIO		*header;

} ;

# else // !OS_MACOSX

class MacFile;

class FileIOMac : public FileIO {

    public:
		FileIOMac();
		~FileIOMac();

	void	Set( const StrPtr &name );
	void	Set( const char *name ) { FileSys::Set( name ); }
	
	int	Stat( bool includeRsrcFork = false );

	void	Open( FileOpenMode mode, Error *e );
	void	Write( const char *buf, int len, Error *e );
	int	Read( char *buf, int len, Error *e );
	void	Close( Error *e );
	void	Unlink( Error *e );

	virtual void	Rename( FileSys *target, Error *e );

	offL_t	GetSize();
	void	Seek( offL_t offset, Error * );

    protected:
	MacFile * GetMacFile( Error *e );
	MacFile * CreateMacFile( Error *e );

    private:
	MacFile * mf;
} ;


class FileIOResource : public FileIOMac {

    public:

    			FileIOResource();
    			~FileIOResource();

	virtual int	Stat() { return FileIOMac::Stat( true ); };

	virtual void	Set( const StrPtr &name );
	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

	virtual void	Unlink( Error *e );

    private:
	StrBuf		*resourceData;		// content of resource fork
	int		ioOffset;		// data read from resourceData
	int		hasDotInName;		// resource fork?


} ;


class FileIOApple : public FileIOMac {

    public:

			FileIOApple();
			~FileIOApple();

	virtual void	Open( FileOpenMode mode, Error *e );
	virtual void	Write( const char *buf, int len, Error *e );
	virtual int	Read( char *buf, int len, Error *e );
	virtual void	Close( Error *e );

    private:

	// Split, and combine AppleSingle format

	AppleForkSplit 		*split;
	AppleForkCombine	*combine;
	DataFork		*dataFork;

	// Access to underlying data and %header files.

	FileIO		*data;

    // MAC-BUILD SPECIFIC
    //
    public:
	// Special for detecting files with resource forks
	virtual int	Stat() { return FileIOMac::Stat( true ); };

	int		HasResourceFork();

    private:
	class FinfoFork		*finfoFork;
	class ResourceFork	*resourceFork;
	class CommentFork	*commentFork;
} ;

# endif // !OS_MACOSX

