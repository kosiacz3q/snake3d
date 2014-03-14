#ifndef VECTOR3F_H
#define VECTOR3F_H

struct Vector4f;

struct Vector3f
{
    public:
        Vector3f();
        Vector3f(const float& xp,const float& yp,const float& zp);
        Vector3f(Vector4f vec);

        void smooth(Vector3f vec , float maxDiff );
        void reset(){
        	x = 0;
        	y = 0;
        	z = 0;
        }

        static Vector3f getPartOfDiffrence(Vector3f vec1 , Vector3f vec2 , float part);
        static void fillVector(Vector3f src , Vector3f& dest , float part);
        static void moveCloseToVector(Vector3f src , Vector3f& dest , float part);

        float x;
        float y;
        float z;

        Vector3f operator+(const Vector3f& vec );
        void operator+=(const Vector3f& vec );
        Vector3f operator-(const Vector3f& vec );
        void operator-=(const Vector3f& vec );
        bool operator==(const Vector3f& vec );
        void operator*=(const float& c );
        Vector3f operator*(const float& c );
        void operator*=(const int& c );

    protected:
    private:
};

struct Vector2f
{
	float x;
	float y;
	Vector2f();
	Vector2f(const float& xp,const float& yp);
	Vector2f operator+(const Vector2f& vec );
	void operator+=(const Vector2f& vec );
	Vector2f operator-(const Vector2f& vec );
	void operator-=(const Vector2f& vec );
	bool operator==(const Vector2f& vec );
	void operator*=(const float& c );
	void operator*=(const int& c );

};

struct Vector4f
{
    public:
		Vector4f();
		Vector4f(const float& xp,const float& yp,const float& zp , const float& wp);
        float x;
        float y;
        float z;
        float w;

        Vector4f operator+(const Vector4f& vec );
        void operator+=(const Vector4f& vec );
        Vector4f operator-(const Vector4f& vec );
        void operator-=(const Vector4f& vec );
        bool operator==(const Vector4f& vec );
        void operator*=(const float& c );
        void operator*=(const int& c );


    protected:
    private:
};




#endif // VECTOR3F_H
