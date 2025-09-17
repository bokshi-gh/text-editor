GREEN='\033[0;32m'
NC='\033[0m' # No Color (reset)

rm -rf build dist
mkdir -p build
cd build

echo -e "${GREEN}[GENERATING BUILD FILES]${NC}"
cmake ..
echo ""

echo -e "${GREEN}[BUILDING THE PROJECT]${NC}"
cmake --build .
echo ""

echo -e "${GREEN}[INSTALLING THE PROJECT]${NC}"
cmake --install . --prefix ../dist

