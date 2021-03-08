import ssl

from urllib.error import HTTPError
from urllib.request import urlopen

from selectolax.parser import HTMLParser


class Ajou:
    @staticmethod
    def parse(limit=None):
        ADDRESS = "https://www.ajou.ac.kr/kr/ajou/notice.do"
        if limit is None:
            limit = 30
        url = f"{ADDRESS}?mode=list&articleLimit={limit}&article.offset=0"

        """공지 파서 메인

        Args:
            url (str, optional): 홈페이지 URL (with admin options). Defaults to None.
            length (int, optional): 몇 개의 공지를 읽을 것인가. Defaults to 10.

        Returns:
            ids, posts, dates, writers, length (list, optional): length에 따른 공지 목록을 전부 불러온다.
        """

        context = ssl._create_unverified_context()
        try:
            result = urlopen(url, timeout=2.0, context=context)
        except HTTPError:
            print("Seems like the server is down now.")
            return None, 0  # make entity
        except TimeoutError:
            print("It's taking too long to load website.")
            return None, 0  # make entity

        html = result.read().decode("utf-8")
        soup = HTMLParser(html)
        no_post = soup.css_first("td.b-no-post")
        if no_post:
            return None, 0  # make entity

        ids = soup.css("td.b-num-box")
        posts = soup.css("div.b-title-box > a")
        # links will be generated by posts[i] href
        dates = soup.css("span.b-date")
        writers = soup.css("span.b-writer")
        length = len(ids)

        ids = soup.css("td.b-num-box")
        posts = soup.css("div.b-title-box > a")
        dates = soup.css("span.b-date")
        writers = soup.css("span.b-writer")

        print("Successfully called:", length)
        print("Posts:", posts[0].text(strip=True))
        return ids, posts, dates, writers, length

