import {
  IOptions,
  IChatItem,
  Language,
  VoiceType,
} from "@/types";
import { createAsyncThunk, createSlice, PayloadAction } from "@reduxjs/toolkit";
import {
  EMobileActiveTab,
  DEFAULT_OPTIONS,
  COLOR_LIST
} from "@/common/constant";
import {
  apiReloadPackage,
  apiFetchGraphs,
  apiFetchInstalledAddons,
  apiFetchGraphDetails,
  apiUpdateGraph,
  apiSaveProperty,
} from "@/common/request"
import {
  setOptionsToLocal,
} from "@/common/storage"
import { AddonDef, Graph } from "@/common/graph";

export interface InitialState {
  options: IOptions;
  roomConnected: boolean;
  agentConnected: boolean;
  rtmConnected: boolean;
  themeColor: string;
  language: Language;
  voiceType: VoiceType;
  chatItems: IChatItem[];
  selectedGraphId: string;
  graphList: string[];
  graphMap: Record<string, Graph>;
  addonModules: AddonDef.Module[]; // addon modules
  mobileActiveTab: EMobileActiveTab;
}

const getInitialState = (): InitialState => {
  return {
    options: DEFAULT_OPTIONS,
    themeColor: COLOR_LIST[0].active,
    roomConnected: false,
    agentConnected: false,
    rtmConnected: false,
    language: "en-US",
    voiceType: "male",
    chatItems: [],
    selectedGraphId: "",
    graphList: [],
    graphMap: {},
    addonModules: [],
    mobileActiveTab: EMobileActiveTab.AGENT,
  };
};

export const globalSlice = createSlice({
  name: "global",
  initialState: getInitialState(),
  reducers: {
    setOptions: (state, action: PayloadAction<Partial<IOptions>>) => {
      state.options = { ...state.options, ...action.payload };
      setOptionsToLocal(state.options);
    },
    setThemeColor: (state, action: PayloadAction<string>) => {
      state.themeColor = action.payload;
      document.documentElement.style.setProperty(
        "--theme-color",
        action.payload
      );
    },
    setRoomConnected: (state, action: PayloadAction<boolean>) => {
      state.roomConnected = action.payload;
    },
    setRtmConnected: (state, action: PayloadAction<boolean>) => {
      state.rtmConnected = action.payload;
    },
    addChatItem: (state, action: PayloadAction<IChatItem>) => {
      const { userId, text, isFinal, type, time } = action.payload;
      const LastFinalIndex = state.chatItems.findLastIndex((el) => {
        return el.userId == userId && el.isFinal;
      });
      const LastNonFinalIndex = state.chatItems.findLastIndex((el) => {
        return el.userId == userId && !el.isFinal;
      });
      let LastFinalItem = state.chatItems[LastFinalIndex];
      let LastNonFinalItem = state.chatItems[LastNonFinalIndex];
      if (LastFinalItem) {
        // has last final Item
        if (time <= LastFinalItem.time) {
          // discard
          console.log(
            "[test] addChatItem, time < last final item, discard!:",
            text,
            isFinal,
            type
          );
          return;
        } else {
          if (LastNonFinalItem) {
            console.log(
              "[test] addChatItem, update last item(none final):",
              text,
              isFinal,
              type
            );
            state.chatItems[LastNonFinalIndex] = action.payload;
          } else {
            console.log(
              "[test] addChatItem, add new item:",
              text,
              isFinal,
              type
            );
            state.chatItems.push(action.payload);
          }
        }
      } else {
        // no last final Item
        if (LastNonFinalItem) {
          console.log(
            "[test] addChatItem, update last item(none final):",
            text,
            isFinal,
            type
          );
          state.chatItems[LastNonFinalIndex] = action.payload;
        } else {
          console.log("[test] addChatItem, add new item:", text, isFinal, type);
          state.chatItems.push(action.payload);
        }
      }
      state.chatItems.sort((a, b) => a.time - b.time);
    },
    setAgentConnected: (state, action: PayloadAction<boolean>) => {
      state.agentConnected = action.payload;
    },
    setLanguage: (state, action: PayloadAction<Language>) => {
      state.language = action.payload;
    },
    setSelectedGraphId: (state, action: PayloadAction<string>) => {
      state.selectedGraphId = action.payload;
    },
    setGraphList: (state, action: PayloadAction<string[]>) => {
      state.graphList = action.payload;
    },
    setVoiceType: (state, action: PayloadAction<VoiceType>) => {
      state.voiceType = action.payload;
    },
    setMobileActiveTab: (state, action: PayloadAction<EMobileActiveTab>) => {
      state.mobileActiveTab = action.payload;
    },
    reset: (state) => {
      Object.assign(state, getInitialState());
      document.documentElement.style.setProperty(
        "--theme-color",
        COLOR_LIST[0].active
      );
    },
    setGraph: (state, action: PayloadAction<Graph>) => {
      let graphMap = JSON.parse(JSON.stringify(state.graphMap));
      graphMap[action.payload.id] = action.payload;
      state.graphMap = graphMap;
    },
    setAddonModules: (state, action: PayloadAction<Record<string, any>[]>) => {
      state.addonModules = JSON.parse(JSON.stringify(action.payload));
    }
  },
});

// Initialize graph data
export const initializeGraphData = createAsyncThunk(
  "global/initializeGraphData",
  async (_, { dispatch }) => {
    try {
      console.log("Starting to fetch graphs");
      
      // First try to reload packages
      try {
        const reloadResult = await apiReloadPackage();
        console.log("Package reload result:", reloadResult);
      } catch (error) {
        console.error("Package reload failed:", error);
        // Continue even if package reload fails
      }
      
      // Then fetch graphs and modules
      try {
        const fetchedGraphs = await apiFetchGraphs();
        console.log("Successfully fetched graphs:", fetchedGraphs);
        dispatch(setGraphList(fetchedGraphs.map((graph) => graph.id)));
      } catch (error) {
        console.error("Error fetching graphs:", error);
        throw new Error(`Failed to fetch graphs: ${error.message}`);
      }

      try {
        const modules = await apiFetchInstalledAddons();
        console.log("Successfully fetched modules:", modules);
        dispatch(setAddonModules(modules));
      } catch (error) {
        console.error("Error fetching addons:", error);
        throw new Error(`Failed to fetch addons: ${error.message}`);
      }
      
    } catch (error) {
      console.error("Failed to initialize graph data:", error);
      throw error;
    }
  }
);

// Fetch graph details
export const fetchGraphDetails = createAsyncThunk(
  "global/fetchGraphDetails",
  async (graphId: string, { dispatch }) => {
    const graph = await apiFetchGraphDetails(graphId);
    dispatch(setGraph(graph));
  }
);

// Update a graph
export const updateGraph = createAsyncThunk(
  "global/updateGraph",
  async (
    { graphId, updates }: { graphId: string; updates: Partial<Graph> },
    { dispatch, rejectWithValue }
  ) => {
    try {
      await apiUpdateGraph(graphId, updates);
      await apiSaveProperty();
      const updatedGraph = await apiFetchGraphDetails(graphId);
      dispatch(setGraph(updatedGraph));
      return updatedGraph; // Optionally return the updated graph
    } catch (error: any) {
      // Handle error gracefully
      console.error("Error updating graph:", error);
      return rejectWithValue(error.response?.data || error.message);
    }
  }
);

export const {
  reset,
  setOptions,
  setRoomConnected,
  setAgentConnected,
  setRtmConnected,
  setVoiceType,
  addChatItem,
  setThemeColor,
  setLanguage,
  setSelectedGraphId,
  setGraphList,
  setMobileActiveTab,
  setGraph,
  setAddonModules,
} = globalSlice.actions;

export default globalSlice.reducer;
