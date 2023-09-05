#include <glm/glm.hpp>
#include <model.hpp>

glm::vec3 computeNormal(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {
    glm::vec3 edge1 = p2 - p1;
    glm::vec3 edge2 = p3 - p1;
    return glm::normalize(glm::cross(edge1, edge2));
}

bool isPOppositeSideFromObserver(const glm::vec3& normalOfQ, const glm::vec3& pointOnQ, const glm::vec3& observerPosition, const glm::vec3& centerOfP) {
    glm::vec3 vectorFromQToP = centerOfP - pointOnQ;
    glm::vec3 vectorFromQToObserver = observerPosition - pointOnQ;
    float dotProduct1 = glm::dot(normalOfQ, vectorFromQToP);
    float dotProduct2 = glm::dot(normalOfQ, vectorFromQToObserver);

    return dotProduct1 * dotProduct2 < 0;
}

// true - P is closer to observer than Q
bool compareFaces(const glm::mat4& trans, std::vector<glm::vec4> P, std::vector<glm::vec4> Q, const glm::vec3& observer) {
    for(auto& point : P) {
        point = trans * point;
    }

    for(auto& point : Q) {
        point = trans * point;
    }

    glm::vec3 normalQ = computeNormal(
            Q.at(0), Q.at(1), Q.at(2)
    );

    glm::vec3 centerOfP = glm::vec3(0.0f, 0.0f, 0.0f);
    for(auto& point : P) {
        centerOfP += point.xyz();
    }
    centerOfP /= P.size();

    if(isPOppositeSideFromObserver(normalQ, Q.at(0), observer, centerOfP)) {
        return true;
    }
    return false;
}


struct FaceRepresent {
    std::vector<glm::vec4> points;
    int index;
};

struct CubeRepresent {
    std::vector<FaceRepresent> faces;
    glm::mat4 transformMatrix;
    glm::vec3 observer;

    void sort() {
        std::sort(faces.begin(), faces.end(), [this](const FaceRepresent &a, const FaceRepresent &b) {
            // The most far should be first
            return compareFaces(transformMatrix, a.points, b.points, observer);
        });
    }
};

std::vector<int> getIndexesOrder(const glm::mat4& trans, const glm::vec3& observer){
    std::vector<FaceRepresent> faces;
    faces.reserve(6);
    faces.emplace_back(FaceRepresent{.points = frontVertices, .index = 0});
    faces.emplace_back(FaceRepresent{.points = backVertices, .index = 6});
    faces.emplace_back(FaceRepresent{.points = leftVertices, .index = 12});
    faces.emplace_back(FaceRepresent{.points = rightVertices, .index = 18});
    faces.emplace_back(FaceRepresent{.points = bottomVertices, .index = 24});
    faces.emplace_back(FaceRepresent{.points = topVertices, .index = 30});

    CubeRepresent y;
    y.faces = faces;
    y.transformMatrix = trans;
    y.observer = observer;

    y.sort();

    std::vector<int> result;
    result.reserve(6);
    for(auto& face : y.faces) {
        result.push_back(face.index);
    }
    return result;
}
